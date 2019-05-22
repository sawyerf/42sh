#include "sh_core.h"

void	del_job(t_job *j)
{
	t_job *save;
	t_job *iter;

	ft_strdel(&j->cmd_ln);
	save = j->next;
	free(j);
	if ((!g_sh.job_lst) || (j == g_sh.job_lst))
	{
		g_sh.job_lst = NULL;
		return ;
	}
	iter = g_sh.job_lst;
	while ((iter->next) && (iter->next != j))
		iter = iter->next;
	iter->next = save;
}
