#include "jobctl.h"

void	register_job(t_job *job)
{
	t_job *iter;
	size_t count;

	if (!g_sh.job_lst)
	{
		job->job_id = 1;
		g_sh.job_lst = job;
	}
	else
	{
		count = 0;
		iter = g_sh.job_lst;
		while (iter)
		{
			if (iter == job)
				return;
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
