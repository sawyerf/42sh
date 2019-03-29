/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:16:45 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/29 20:17:59 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

int	ft_unset(t_cmd_tab *cmd)
{
	int i;

	i = 1;
	while (cmd->av[i])
	{
		if ((!(g_sh.env = envdel(g_sh.env, cmd->av[i])))
			|| (!(g_sh.local = envdel(g_sh.local, cmd->av[i]))))
			return (MEMERR);
		i++;
	}
	return (0);
}

int	ft_unsetenv(t_cmd_tab *cmd)
{
	int	i;

	if (cmd->av[1] == NULL)
	{
		putstr_stderr("usage: unsetenv [NAME] ..\n");
		return (-1);
	}
	else
	{
		i = 0;
		while (cmd->av[i] != NULL)
		{
			if (!(g_sh.env = envdel(g_sh.env, cmd->av[i])))
				return (MEMERR);
			i++;
		}
	}
	return (0);
}
