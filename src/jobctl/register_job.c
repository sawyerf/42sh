/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_job.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 18:48:13 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/01 19:50:15 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobctl.h"

static void	first_job(t_job *job)
{
	job->job_id = 1;
	g_sh.job_lst = job;
}

void		register_job(t_job *job)
{
	t_job	*iter;
	size_t	count;

	if (!g_sh.job_lst)
		first_job(job);
	else
	{
		count = 0;
		iter = g_sh.job_lst;
		while (iter)
		{
			if (iter == job)
				return ;
			iter = iter->next;
			count++;
		}
		iter = g_sh.job_lst;
		while (iter->next)
			iter = iter->next;
		iter->next = job;
		job->prev = iter;
		job->job_id = 1 + count;
	}
}
