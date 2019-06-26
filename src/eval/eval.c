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

int			background_fork(pid_t pid, t_job *job, t_ast_node *t)
{
	if (setpgid_wrap(pid, job) == -1)
		exit_wrap(MEMERR, NULL);
	g_sh.mode = NONINTERACTIVE;
	reset_sig();
	eval_tree(t->left);
	waitpid(job->pgid, NULL, WUNTRACED);
	waitpid(WAIT_ANY, NULL, 0);
	//ft_printf("[%d]Background Job finished\n", job->pgid);
	exit_wrap(0, NULL);
	return (0);
}

int			background_subshell(t_ast_node *tree)
{
	t_job	*job;
	pid_t	pid;
	
	if (!(job = make_job(0)) || (!(job->cmd_ln = make_cmdline(tree->start, tree->end, 1))))
		return (MEMERR);
	if ((pid = fork()) == -1)
		return (MEMERR); //should fork error or sthing
	if (pid == 0)
	{
		background_fork(pid, job, tree);
	}	
	if (setpgid_wrap(pid, job) == -1)
		ft_dprintf(STDERR_FILENO, "42sh: setpgid fail for %d\n", pid);
	register_job(job);
	ft_dprintf(STDERR_FILENO, "[%d] %d\n", job->job_id, job->pgid);
	tcgetattr(STDIN_FILENO, &(job->save_tio));
	g_sh.lastback = job->pgid;
	g_sh.previous_j = g_sh.current_j;
	g_sh.current_j = job;
	return (0);
}

static int	eval_sep(t_ast_node *tree)
{
	t_job	*job;
	pid_t	pid;

	job = NULL;
	pid = 0;
	if ((tree->type == AMPERS) && (g_sh.mode == INTERACTIVE))
	{
		if (background_subshell(tree))
			return (MEMERR);
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
