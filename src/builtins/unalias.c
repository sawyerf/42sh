/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:57:28 by apeyret           #+#    #+#             */
/*   Updated: 2019/05/27 19:20:55 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "sh_core.h"

extern t_sh	g_sh;

int		unalias(t_cmd_tab *cmd)
{
	int		count;

	count = 0;
	if (!cmd->av[1])
	{
		ft_dprintf(2, "unalias: usage: unalias [name ...]\n");
		return (0);
	}
	while (cmd->av[count])
	{
		if (!(g_sh.alias = envdel(g_sh.alias, cmd->av[count])))
			return (MEMERR);
		count++;
	}
	return (0);
}
