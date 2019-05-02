/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 11:48:18 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/12 16:53:24 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

int	pipe_recursion(t_cmd_tab *to, t_cmd_tab *from, t_job *job)
{
	int pipes[2];
	int pid;

	if ((pipe(pipes) != 0) || ((pid = fork()) == -1))
		return (MEMERR);
	if (pid == 0)
	{
//		if (setpgid_wrap(pid, job) == -1)
//			exit_wrap(MEMERR, from);
		if (to)
		{
			if (dup2(pipes[1], STDOUT_FILENO) == -1)
				return (PIPEFAIL);
			close(pipes[0]);
		}
		spawn_in_pipe(from);
	}
	if ((g_sh.mode == INTERACTIVE) && (setpgid_wrap(pid, job) == -1))
		return (MEMERR);
	if (to)
	{
		if (dup2(pipes[0], STDIN_FILENO) == -1)
			return (PIPEFAIL);
		close(pipes[1]);
		return (pipe_recursion(to->next, to, job));
	}
//	if ((g_sh.mode != INTERACTIVE) || ((job) && (job->fg)))
		//wait_wrapper(from, pid);
	return (from->exit_status);
}

int	eval_pipe(t_cmd_tab *pipeln, t_job *job)
{
	pid_t	pid;
 	int		ret;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if ((g_sh.mode == INTERACTIVE) && (setpgid_wrap(pid, job) == -1))
			exit_wrap(MEMERR, pipeln);
		if (job->fg)
			tcsetpgrp(STDIN_FILENO, job->pgid);
		reset_sig();
  		ret = pipe_recursion(pipeln->next, pipeln, job);
		waitpid(WAIT_ANY, NULL, 0);
		exit_wrap(ret, pipeln);
	}
	if ((g_sh.mode == INTERACTIVE) && (setpgid_wrap(pid, job) == -1))
		return (MEMERR);
	if (g_sh.mode != INTERACTIVE)
		wait_wrapper(pipeln, pid);
	else if ((job) && (job->fg))
		fg_job(job, 0);
	return (0);
}

int	exec_pipeline(t_ast_node *tree, t_job *job)
{
	t_cmd_tab	*cmd_tab;
	int			ret;
	t_cmd_tab	*iter;

	ret = 0;
	if (!(cmd_tab = expand_pipeline(tree->pipeline)))
		return (MEMERR);
	if ((g_sh.mode == INTERACTIVE)
		&& (!job) && (!(job = make_job(1))))
		return (MEMERR);
	if (cmd_tab->next)
		ret = eval_pipe(cmd_tab, job);
	else
		ret = launch_command(cmd_tab, job);
	iter = cmd_tab;
	while (iter->next)
		iter = iter->next;
	tree->exit_status = iter->exit_status;
	g_sh.status = tree->exit_status;
	free_cmd_tab_lst(cmd_tab);
	return (ret);
}

/*
int	launch_job(t_job *job, int fg)
{

}*/
