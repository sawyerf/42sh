/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:16:45 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/10 17:42:03 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	error_handle(t_cmd_tab *cmd)
{
	if (cmd->av[1] == NULL)
	{
		putstr_stderr("usage: unsetenv [NAME] ..\n");
		return (-1);
	}
	if (cmd->av[1][0] == 0)
	{
		ft_dprintf(STDERR_FILENO,
			"21sh: setenv : variable name cannot be empty\n");
		return (-1);
	}
	return (0);
}

int			ft_unset(t_cmd_tab *cmd)
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

int			ft_unsetenv(t_cmd_tab *cmd)
{
	int	i;

	if (error_handle(cmd))
		return (-1);
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
