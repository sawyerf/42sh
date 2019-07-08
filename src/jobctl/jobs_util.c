/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 18:48:03 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 15:48:57 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

int			refresh_jobs(void)
{
	t_job *j;
	pid_t chld;

	j = g_sh.job_lst;
	while (j)
	{
		chld = waitpid(-(j->pgid), &(j->status),
				WUNTRACED | WNOHANG | WCONTINUED);
		if (WIFSIGNALED(j->status))
			j->completed = 1;
		if ((chld > 0) && (WIFEXITED(j->status)))
			j->completed = 1;
		if (WIFSTOPPED(j->status))
			j->stopped = 1;
		else
			j->stopped = 0;
		j = j->next;
	}
	return (0);
}

static void	job_handle_curr(t_job *j)
{
	if (j == g_sh.current_j)
	{
		g_sh.current_j = g_sh.previous_j;
		if (g_sh.current_j)
			g_sh.previous_j = g_sh.current_j->prev;
	}
	else if (j == g_sh.previous_j)
	{
		g_sh.previous_j = j->prev;
	}
}

void		del_job(t_job *j)
{
	t_job *save_n;
	t_job *iter;

	job_handle_curr(j);
	ft_strdel(&j->cmd_ln);
	save_n = j->next;
	free(j);
	if (j == g_sh.job_lst)
	{
		if (!save_n)
			g_sh.job_lst = NULL;
		else
			g_sh.job_lst = save_n;
		return ;
	}
	iter = g_sh.job_lst;
	while ((iter->next) && (iter->next != j))
		iter = iter->next;
	iter->next = save_n;
	if (save_n)
		save_n->prev = iter;
}

int			ignore_notif(t_job *job)
{
	int signum;

	if (job->fg)
		return (0);
	if (WIFSIGNALED(job->status))
	{
		signum = WTERMSIG(job->status);
		if ((signum == SIGINT) || (signum == SIGPIPE))
			return (0);
	}
	return (1);
}

void		clean_jobs(void)
{
	t_job *ptr;
	t_job *save;

	refresh_jobs();
	ptr = g_sh.job_lst;
	while (ptr)
	{
		save = ptr->next;
		if (ptr->completed)
		{
			if ((!ptr->notified) && (ignore_notif(ptr)))
				ft_printf("[%d] %d '%s' completed\n",
					ptr->job_id, ptr->pgid, ptr->cmd_ln);
			del_job(ptr);
		}
		ptr = save;
	}
}
