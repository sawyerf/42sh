/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 19:28:02 by ktlili            #+#    #+#             */
/*   Updated: 2019/05/04 19:28:31 by ktlili           ###   ########.fr       */
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
	ft_printf("waitpid ret %d\n", pid);
	if (WIFEXITED(job->status))
	{
		job->completed = 1;
		job->notified = 1;
		ft_printf("job %d exited normally\n", job->pgid);
	}
	else
	{
		ft_printf("job %d signaled\n", job->pgid);
	}
	register_job(job);
	return;
}


int		fg_job(t_job *job, int cont)
{
	tcsetpgrp(STDIN_FILENO, job->pgid);
	if (cont)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &(job->save_tio));
		if (kill(job->pgid, SIGCONT) < 0)
			ft_dprintf(STDERR_FILENO, "42sh: Error sending cont to pgid %d", job->pgid);
	}
	wait_job(job);
	tcgetattr(STDIN_FILENO, &(job->save_tio)); // save job terminal modes
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
