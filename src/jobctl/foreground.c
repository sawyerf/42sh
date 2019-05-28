/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 19:28:02 by ktlili            #+#    #+#             */
/*   Updated: 2019/05/28 16:19:15 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobctl.h"


void	update_job(t_job *job)
{
	if (!job->pgid)
		job->pgid = WAIT_ANY;
	waitpid(job->pgid, &(job->status), WNOHANG);
}

void	wait_job(t_job *job)
{
	pid_t pid;

	if (!job->pgid)
		job->pgid = WAIT_ANY;
	pid = waitpid(job->pgid, &(job->status), WUNTRACED);
	ft_printf("===DEBUG===waitpid ret %d\n", pid);
	register_job(job);
	if (WIFEXITED(job->status))
	{
		job->completed = 1;
		job->notified = 1;
		ft_printf("===DEBUG===job %d exited normally\n", job->pgid);
	}
	else if (WIFSIGNALED(job->status))
	{
		ft_printf("[%d] %d signal num %d       %s\n", job->job_id, job->pgid, WTERMSIG(job->status), job->cmd_ln);
	}
	else if (WIFSTOPPED(job->status))
	{
		ft_printf("[%d] %d suspended       %s\n", job->job_id, job->pgid, job->cmd_ln);
		g_sh.previous_j = g_sh.current_j;
		g_sh.current_j = job;
	
	}
	return;
}


int		fg_job(t_job *job, int cont)
{
	tcsetpgrp(STDIN_FILENO, job->pgid);
	if (cont)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &(job->save_tio));
		if (kill(job->pgid, SIGCONT) < 0)
		{
			ft_dprintf(STDERR_FILENO, "42sh: Error sending cont to pgid %d", job->pgid);
			return (0); // maybe not ?
		}	
	}
	wait_job(job);
	tcgetattr(STDIN_FILENO, &(job->save_tio)); // save job terminal modes
	tcsetattr(STDIN_FILENO, TCSADRAIN, &(g_sh.term_save)); // reset our termios
	tcsetpgrp(STDIN_FILENO, getpgrp());
	return (0);
}

int bg_job(t_job *job, int cont)
{
	if (cont)
	{
		if (kill(job->pgid, SIGCONT) < 0)
			ft_dprintf(STDERR_FILENO, "42sh: Error sending cont to pgid %d", job->pgid);
	}
	register_job(job);
	return (0);
}
