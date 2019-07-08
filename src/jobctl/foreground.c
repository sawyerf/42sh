/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 19:28:02 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 17:05:16 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobctl.h"

void	update_job(t_job *job)
{
	if (!job->pgid)
		job->pgid = WAIT_ANY;
	waitpid(job->pgid, &(job->status), WNOHANG);
}

void	finish_job(t_job *job)
{
	job->completed = 1;
	job->notified = 1;
}

void	wait_job(t_job *job)
{
	pid_t pid;

	pid = job->pgid;
	if ((!job->pgid) || (g_sh.mode != INTERACTIVE))
		pid = WAIT_ANY;
	if ((pid = waitpid(pid, &(job->status), WUNTRACED)) == -1)
	{
		ft_dprintf(STDERR_FILENO, "42sh: wait failed for '%s'\n", job->cmd_ln);
	}
	register_job(job);
	if (WIFEXITED(job->status))
		finish_job(job);
	else if (WIFSIGNALED(job->status))
		print_sigexit(job);
	else if (WIFSTOPPED(job->status))
	{
		ft_printf("[%d] %d suspended       %s\n",
				job->job_id, job->pgid, job->cmd_ln);
		if (g_sh.current_j != job)
			g_sh.previous_j = g_sh.current_j;
		g_sh.current_j = job;
	}
}

int		fg_job(t_job *job, int cont)
{
	tcsetpgrp(STDIN_FILENO, job->pgid);
	if (cont)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &(job->save_tio));
		if (killpg(job->pgid, SIGCONT) < 0)
		{
			ft_dprintf(STDERR_FILENO,
				"42sh: Error sending cont to pgid %d as fg\n", job->pgid);
			return (0);
		}
	}
	wait_job(job);
	tcgetattr(STDIN_FILENO, &(job->save_tio));
	tcsetattr(STDIN_FILENO, TCSADRAIN, &(g_sh.term_save));
	tcsetpgrp(STDIN_FILENO, getpgrp());
	return (0);
}

int		bg_job(t_job *job, int cont)
{
	if (cont)
	{
		if (killpg(job->pgid, SIGCONT) < 0)
			ft_dprintf(STDERR_FILENO,
				"42sh: Error sending cont to pgid %d as bg\n", job->pgid);
	}
	register_job(job);
	g_sh.lastback = job->pgid;
	return (0);
}
