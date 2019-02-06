/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 11:48:18 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/01 18:48:23 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

int		pipe_callback(t_cmd_tab *to, t_cmd_tab *from)
{
	int pipes[2];
	int pid;

	if (pipe(pipes) != 0)
		return (PIPEFAIL);
	pid = fork();
	if (pid == -1)
		return (-1); //should be exec error
	if (pid == 0)
	{
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		if (from->next != NULL)
			pipe_callback(from, from->next);
		execute_command(from);
		exit(0);
	}
	dup2(pipes[0], STDIN_FILENO);
	close(pipes[1]);
	wait (NULL);
	execute_command(to);
	exit(0);
	return (0);
}

int	eval_pipe(t_cmd_tab *cmd)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		pipe_callback(cmd, cmd->next);
		exit(0);
	}
	wait(NULL);
	return (0);
}

void	token_to_array(t_token *word, char **array)
{
	int i;

	i = 0;
	while (word)
	{
		array[i] = word->data.str;
		word = word->next;
		i++;
	}
	return;
}


char **expand_word_lst(t_token *word)
{
	size_t lst_len;
	char	**cmd_av;
	t_token	*iter;
	t_token *save;

	iter = word;
	while (iter)
	{
		save = iter->next;
		if (ft_wordexp(iter) == MEMERR)
			return (NULL);
		iter = save;
	}
	iter = word;
	lst_len = 0;
	while (iter)
	{
		lst_len++;
		iter = iter->next;
	}
	if (!(cmd_av = ft_memalloc((lst_len + 1) * sizeof(char*))))
		return (NULL);
	token_to_array(word, cmd_av);
	return (cmd_av);
}

t_cmd_tab	*expand_simple_cmd(t_simple_cmd *before)
{
	t_cmd_tab *after;

	if (!(after = ft_memalloc(sizeof(t_cmd_tab))))
			return (NULL);	
	if ((after->av = expand_word_lst(before->word_lst))== NULL)
		return (NULL);
/* all assignements are done in subshell
	if ((after->process_env = lst_to_tab(*g_environ, 0) ) == NULL) 
		return (NULL);*/
	after->redir_lst = before->redir_lst;
	return (after);
}

/*
 * we need to invert cmd list while expanding shit 
 */
t_cmd_tab *expand_pipeline(t_simple_cmd *cmd_lst)
{
	t_simple_cmd 	*iter;
	t_cmd_tab		*cmd_tab;
	t_cmd_tab		*head;

	iter = cmd_lst;	
	head = NULL;
	while (iter)
	{
		if (!(cmd_tab = expand_simple_cmd(iter)))
			return (NULL);
		cmd_tab->next = head;
		head = cmd_tab;
		iter = iter->next;
	}
	return (head);
}

int	exec_pipeline(t_ast_node *tree)
{
	t_cmd_tab 	*cmd_tab;
	int			ret;

	if (!(cmd_tab = expand_pipeline(tree->pipeline)))
		return (MEMERR);
	if (cmd_tab->next)
		ret = eval_pipe(cmd_tab);
	else /*spawn bin here*/
		ret = spawn_command(cmd_tab);
	if (ret)
		return (ret);
	tree->exit_status = cmd_tab->exit_status;
	return (0);
}

int	eval_tree(t_ast_node *tree)
{
	if (tree->type == SEMI_COL)
	{
		eval_tree(tree->left);
		eval_tree(tree->right);
		return (0);
	}
	else if (tree->type == AND_IF)
	{
		eval_tree(tree->left);
		if (tree->left->exit_status == 0)
		{
			eval_tree(tree->right);
			tree->exit_status = tree->right->exit_status;
		}
		return (0);
	}
	else if (tree->type == OR_IF)
	{
		eval_tree(tree->left);
		if (tree->left->exit_status != 0)
		{
			eval_tree(tree->right);
			tree->exit_status = tree->right->exit_status;	
		}
		tree->exit_status = tree->left->exit_status;
		return (0);
	}
	else if (tree->type == PIPE)
	{
		exec_pipeline(tree);
		return (0);
	}
	ft_printf("fatal error in eval_tree: unknown node type\n");
	exit(1);	
}
