/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:34:05 by ktlili            #+#    #+#             */
/*   Updated: 2019/03/27 15:01:59 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
/* replace t_cmd_tab with new cmd struct
 *
 *
 * */

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
	i = 0;
	if (!valid_env_name(cmd->av[1]))
	{
		putstr_stderr("setenv: variable name is invalid\n");
		return (-1);
	}
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
