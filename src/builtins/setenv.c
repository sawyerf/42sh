/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:34:05 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/04 14:00:14 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_set(t_cmd_tab *cmd)
{
	(void)cmd;
	print_env_tab(g_sh.local);
	return (0);
}

int	setenv_wrapper(t_cmd_tab *cmd)
{
	int i;

	if (cmd->av[1] == NULL)
	{
		ft_printf("usage: setenv [NAME] [VALUE]\n");
		return (-1);
	}
	if ((cmd->av[1][0] == 0) || (!valid_env_name(cmd->av[1])))
	{
		putstr_stderr("setenv: variable name is invalid\n");
		return (-1);
	}
	i = 0;
	while (cmd->av[i] != NULL)
	{
		i++;
		if (i > 3)
		{
			putstr_stderr("setenv: Too many arguments\n");
			return (-1);
		}
	}
	if (!(g_sh.env = envaddstr(g_sh.env, cmd->av[1], cmd->av[2])))
		return (MEMERR);
	return (0);
}
