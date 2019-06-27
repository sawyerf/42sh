/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 17:55:48 by tduval            #+#    #+#             */
/*   Updated: 2019/06/26 13:56:11 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_job		*start;
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

t_job	*jobs_conv_min(char *s)
{
	(void)s;
	if (g_sh.previous_j)
		return (g_sh.previous_j);
	else
		return (jobs_conv_pct(s));
	return (NULL);
}

t_job	*jobs_conv_cmd(char *s)
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
		if (!ft_strncmp(s, j->cmd_ln, ft_strlen(s)))
			return (j);
		j = j->next;
	}
	return (NULL);
}
