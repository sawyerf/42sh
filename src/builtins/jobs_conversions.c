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

t_job	*jobs_conversion(char *arg)
{
	if ((!arg) || (*arg != '%') || !(*(arg + 1)))
		return (NULL);
	if (*(arg + 1) == '%')
		return (jobs_conv_pct(arg + 1));
	else if (*(arg + 1) == '+')
		return (jobs_conv_min(arg + 1));
	else if (*(arg + 1) == '-')
		return (jobs_conv_min(arg + 1));
	else if (ft_isalldigit(arg + 1))
		return (jobs_conv_num(arg + 1));
	else if (*(arg + 1) == '?')
		return (jobs_conv_cmd(arg + 1));
	else
		return (jobs_conv_any(arg + 1));	
}
