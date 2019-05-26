#include "sh_core.h"

void	del_job(t_job *j)
{
	t_job *save;
	t_job *iter;

	ft_strdel(&j->cmd_ln);
	save = j->next;
	free(j);
	if (j == g_sh.job_lst)
	{
		if (!save)
			g_sh.job_lst = NULL;
		else
			g_sh.job_lst = save;
		return;
	}
	iter = g_sh.job_lst;
	while ((iter->next) && (iter->next != j))
		iter = iter->next;
	iter->next = save;
}

void	clean_jobs(void)
{
	t_job *ptr;
	t_job *save;

	ptr = g_sh.job_lst;
	while (ptr)
	{
		save = ptr->next;
		if ((ptr->notified) && (ptr->completed))
			del_job(ptr);
		ptr = save;
	}
}


