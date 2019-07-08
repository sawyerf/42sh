/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:24:33 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 19:30:33 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	jobs_err(char *builtin)
{
	if (g_sh.mode != INTERACTIVE)
	{
		ft_dprintf(STDERR_FILENO, "42sh: %s: no job control\n", builtin);
		return (1);
	}
	if ((!g_sh.job_lst) && (ft_strncmp(builtin, "jobs", 5)))
	{
		ft_dprintf(STDERR_FILENO, "42sh: %s: no jobs running\n", builtin);
		return (1);
	}
	return (0);
}

int	fg(t_cmd_tab *cmd)
{
	t_job *j;

	refresh_jobs();
	if (jobs_err("fg"))
		return (0);
	if ((!cmd->av[1]) && (g_sh.current_j))
	{
		ft_dprintf(STDERR_FILENO, "%s\n", g_sh.current_j->cmd_ln);
		fg_job(g_sh.current_j, 1);
	}
	else
	{
		j = jobs_conversion(cmd->av[1]);
		if ((j) && (!j->completed))
		{
			ft_dprintf(STDERR_FILENO, "%s\n", j->cmd_ln);
			fg_job(j, 1);
		}
		else
			ft_dprintf(STDERR_FILENO, "42sh: fg: '%s': no such job\n",
						cmd->av[1]);
	}
	return (0);
}
