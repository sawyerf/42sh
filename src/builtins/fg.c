/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:24:33 by ktlili            #+#    #+#             */
/*   Updated: 2019/05/03 16:47:49 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


int		fg(t_cmd_tab *cmd)
{
	int job_n;
	int i;
	t_job *iter;
	i = 0;
	if (cmd->av[1])
		job_n = ft_atoi(cmd->av[1]);
	iter = g_sh.job_lst;
	while (iter)
	{
		if (i == job_n)
		{
			fg_job(iter, 1);
			return (0);
		}
		iter = iter->next;
	}
	ft_dprintf(STDERR_FILENO, "42sh: jobs : job not found\n");
	return (1);

}
