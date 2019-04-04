/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:17:24 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/04 13:59:33 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "readline.h"

int	ft_exit(t_cmd_tab *cmd)
{
	int exit_val;
	int i;

	exit_val = 0;
	i = 0;
	if (cmd->av[1] != NULL)
	{
		if (cmd->av[2] != NULL)
		{
			putstr_stderr("exit: too many arguments\n");
			return (0);
		}
		while (cmd->av[1][i] != 0)
		{
			if (!ft_isdigit(cmd->av[1][i]))
			{
				putstr_stderr("exit: numeric argument required\n");
				return (0);
			}
			i++;
		}
		exit_val = ft_atoi(cmd->av[1]);
	}
	hstaddfile(g_sh.env);
	exit(exit_val);
}
