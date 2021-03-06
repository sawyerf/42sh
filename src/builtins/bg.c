/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 18:54:45 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 19:30:50 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		bg(t_cmd_tab *cmd)
{
	t_job *j;

	if (jobs_err("bg"))
		return (0);
	if ((!cmd->av[1]) && (g_sh.current_j))
		bg_job(g_sh.current_j, 1);
	else
	{
		j = jobs_conversion(cmd->av[1]);
		if (j)
			bg_job(j, 1);
		else
			ft_dprintf(STDERR_FILENO, "42sh: bg: '%s': no such job\n",
							cmd->av[1]);
	}
	return (0);
}
