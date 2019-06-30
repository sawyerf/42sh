/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:17:24 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/27 19:23:30 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "sh_core.h"

int		ft_exit(t_cmd_tab *cmd)
{
	if (!exit_jobs())
		return (1);
	if (cmd->av[1])
	{
		if (cmd->av[2] || !ft_strisdigit(cmd->av[1]))
		{
			if (cmd->av[2])
				putstr_stderr("exit: too many arguments\n");
			else
				putstr_stderr("exit: numeric argument required\n");
			return (0);
		}
	}
	global_del();
	if (cmd->av[1])
		exit(ft_atoi(cmd->av[1]));
	exit(g_sh.status);
}
