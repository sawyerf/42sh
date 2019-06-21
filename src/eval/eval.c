/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 11:48:18 by ktlili            #+#    #+#             */
/*   Updated: 2019/06/01 18:52:46 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

static int	eval_sep(t_ast_node *tree)
{
	t_job	*job;
	pid_t	pid;

	job = NULL;
	pid = 0;
	if ((tree->type == AMPERS) && (g_sh.mode == INTERACTIVE))
	{
		if (!(job = make_job(0)) || (!(job->cmd_ln = make_cmdline(tree->start, tree->end, 1))))
			return (MEMERR);
		if ((pid = fork()) == -1)
			return (MEMERR); //should fork error or sthing
		if (pid == 0)
		{
			if (setpgid_wrap(pid, job) == -1)
				exit_wrap(MEMERR, NULL);
			g_sh.mode = NONINTERACTIVE;
			reset_sig();
			eval_tree(tree->left);
			waitpid(job->pgid, NULL, WUNTRACED);
			waitpid(WAIT_ANY, NULL, 0); //tmp
			exit_wrap(0, NULL);
		}	
		if (setpgid_wrap(pid, job) == -1)
			return(MEMERR);
		register_job(job);
		g_sh.previous_j = g_sh.current_j;
		g_sh.current_j = job;
		ft_printf("==DEBUG==job started in bg %d, subshell waiting\n", pid);	
	}
	else 
	{
		if ((tree->left) && (eval_tree(tree->left) == MEMERR))
			return (MEMERR);
	}
	if ((tree->right) && (eval_tree(tree->right) == MEMERR))
		return (MEMERR);
	return (0);
}

static int	eval_and_if(t_ast_node *tree)
{
	if (eval_tree(tree->left) == MEMERR)
		return (MEMERR);
	if (tree->left->exit_status == 0)
	{
		if (eval_tree(tree->right) == MEMERR)
			return (MEMERR);
		tree->exit_status = tree->right->exit_status;
	}
	else
		tree->exit_status = tree->left->exit_status;
	return (0);
}

static int	eval_or_if(t_ast_node *tree)
{
	if (eval_tree(tree->left) == MEMERR)
		return (MEMERR);
	if (tree->left->exit_status != 0)
	{
		if (eval_tree(tree->right) == MEMERR)
			return (MEMERR);
		tree->exit_status = tree->right->exit_status;
	}
	else
		tree->exit_status = tree->left->exit_status;
	return (0);
}

int			eval_tree(t_ast_node *tree)
{
	if (tree == NULL)
		return (-1);
	if ((tree->type == SEMI_COL) || (tree->type == AMPERS)
		|| (tree->type == NEWLINE))
		return (eval_sep(tree));
	else if (tree->type == AND_IF)
		return (eval_and_if(tree));
	else if (tree->type == OR_IF)
		return (eval_or_if(tree));
	else if (tree->type == PIPE)
	{
		if (launch_pipe(tree, NULL) == MEMERR)
			return (MEMERR);
		return (0);
	}
	ft_dprintf(STDERR_FILENO, "21sh: fatal error in eval: unknown node type\n");
	return (-1);
}
