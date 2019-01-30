/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 11:48:18 by ktlili            #+#    #+#             */
/*   Updated: 2019/01/30 17:53:57 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_eval.h"

int		pipe_callback(t_cmd_tab *to, t_cmd_tab *from)
{
	int pipes[2];
	int pid;

	if (pipe(pipes) != 0)
		return (PIPEFAIL);
	if (pid == 0)
	{
		dup2(pipe[1], STDOUT_FILENO);
		close(pipe[0]);
		if (from->next != NULL)
			pipe_callback(from, from->next);
		execute_cmd(from);
	}
	dup2(pipes[0], STDIN_FILENO);
	close(pipes[1]);
	wait (NULL);
	execute_cmd(to);
}


t_cmd_tab	expand_simple_cmd(t_simple_cmd *before)
{
	t_cmd_tab *after;

	if (!(after = ft_memalloc(sizeof(t_cmd_tab))))
			return (NULL);

}

/*
 * we need to invert cmd list while expanding shit 
 */
t_cmd_tab *expand_pipeline(t_simple_cmd *cmd_lst)
{
	t_simple_cmd 	*iter;
	t_cmd_tab		*cmd_tab;

	iter = cmd_lst;	
	while (iter)
	{
		if (expand_simple_cmd(iter) == NULL)
			return (NULL);
		iter = cmd_lst->next;
	}
}

int	exec_pipeline(t_ast_node *tree)
{
	t_cmd_tab *cmd_tab;

	if (!(cmd_tab = expand_pipeline(tree->pipeline)))
		return (MEMERR);
	if (cmd_tab->next)
		ret = pipe_callback(cmd_tab, cmd_tab->next);
	else
		ret = execute_cmd(cmd_tab);
	if (ret)
		return (ret);
	tree->exit_status = cmd_tab->exit_status
	


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
	exit(1)	
}
