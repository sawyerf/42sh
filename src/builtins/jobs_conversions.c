/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_conversions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 18:48:55 by ktlili            #+#    #+#             */
/*   Updated: 2019/06/01 18:49:10 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* return ptr on job if found, null otherwise*/

#include "builtins.h"

t_job	*jobs_conv_pct(char *s)
{
	(void)s;
	if (g_sh.current_j)
		return (g_sh.current_j);
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
	if (g_sh.previous_j)
		return (g_sh.previous_j);
	else
		return (jobs_conv_pct(s));
	return (NULL);
}


t_job 	*jobs_conv_cmd(char *s)
{
	t_job *j;

	j = g_sh.job_lst;
	while (j)
	{
		if (ft_strstr(s, j->cmd_ln))
			return (j);
		j = j->next;
	}
	return (NULL);
}

t_job	*jobs_conv_any(char *s)
{
	t_job *j;

	j = g_sh.job_lst;
	while (j)
	{
		if (!ft_strcmp(s, j->cmd_ln))
			return (j);
		j = j->next;
	}
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
