/* return ptr on job if found, null otherwise*/

#include "builtins.h"

t_job	*jobs_conv_pct(char *s)
{
	(void)s;
	return (NULL);

}

t_job	*jobs_conv_num(char *s)
{
	t_job 		*start;
	size_t		job_id;

	start = g_sh.job_lst; 
	job_id = (size_t)ft_atoi(s);
	while (start)
	{
		if (job_id == start->job_id)
			return (start);
		start = start->next;
	}
	return (NULL);
}

t_job 	*jobs_conv_min(char *s)
{
	(void)s;
	return (NULL);
}


t_job 	*jobs_conv_cmd(char *s)
{
	(void)s;
	return (NULL);
}

t_job	*jobs_conv_any(char *s)
{
	(void)s;
	return (NULL);
}
