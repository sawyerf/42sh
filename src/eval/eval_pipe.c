/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <ktlili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 11:48:18 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/01 19:59:01 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

void	close_p(int pipes[2])
{
	close(pipes[0]);
	close(pipes[1]);
}

int		pipe_recursion(t_cmd_tab *to, t_cmd_tab *from, t_job *job)
{
	int pipes[2];
	int pid;

	if ((pipe(pipes) != 0) || ((pid = fork()) == -1))
		return (PIPEFAIL);
	if (pid == 0)
	{
		if (to)
		{
			if (dup2(pipes[1], STDOUT_FILENO) == -1)
				return (PIPEFAIL);
			close_p(pipes);
		}
		spawn_in_pipe(from);
	}
	if (to)
	{
		if (dup2(pipes[0], STDIN_FILENO) == -1)
			return (PIPEFAIL);
		close_p(pipes);
		return (pipe_recursion(to->next, to, job));
	}
	close(STDIN_FILENO);
	job->pgid = pid;
	return (0);
}

int		pipe_subshell(pid_t pid, t_cmd_tab *pipeln, t_job *job)
{
	int ret;

	if (g_sh.mode == INTERACTIVE)
	{
		if ((!job->pgid) && (setpgid_wrap(pid, job) == -1))
			exit_wrap(MEMERR, pipeln);
		if (job->fg)
			tcsetpgrp(STDIN_FILENO, job->pgid);
	}
	reset_sig();
	if ((ret = pipe_recursion(pipeln->next, pipeln, job)))
		exit_wrap(-1, pipeln);
	waitpid(job->pgid, &(job->status), WUNTRACED);
	waitpid(WAIT_ANY, NULL, 0);
	exit_wrap(WEXITSTATUS(job->status), pipeln);
	return (42);
}

int		eval_pipe(t_cmd_tab *pipeln, t_job *job)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		pipe_subshell(pid, pipeln, job);
	if ((g_sh.mode == INTERACTIVE) && (setpgid_wrap(pid, job) == -1))
		return (MEMERR);
	if (g_sh.mode != INTERACTIVE)
		wait_job(job);
	else if ((job) && (job->fg))
		fg_job(job, 0);
	else
		bg_job(job, 0);
	return (0);
}
