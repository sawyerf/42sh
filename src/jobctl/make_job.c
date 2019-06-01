/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 18:48:07 by ktlili            #+#    #+#             */
/*   Updated: 2019/06/01 18:48:21 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobctl.h"

int		setpgid_wrap(pid_t pid, t_job *job)
{
	if (!pid)
		pid = getpid();
	if (!job->pgid)
		job->pgid = pid;
	if (setpgid(pid, job->pgid) == -1)
		return (-1);
	return (0);	

}

t_job	*make_job(int fg)
{
	t_job	*job;
	
	if (!(job = ft_memalloc(sizeof(t_job))))
		return (NULL);
	ft_bzero(job, sizeof(t_job));
	if (fg)
		job->fg = 1;
	return (job);
}
