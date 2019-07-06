/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:57:28 by apeyret           #+#    #+#             */
/*   Updated: 2019/07/06 17:08:23 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "sh_core.h"

extern t_sh	g_sh;

int		pars_unalias(char **tab, t_pars *pars)
{
	char	c;

	if (!*tab)
	{
		ft_dprintf(2, "unalias: usage: unalias [name ...]\n");
		return (-1);
	}
	pars->opt[0] = 0;
	while (*tab && (c = parser_takeopt("a", *tab, pars->opt, "alias")) && c != '-')
		tab++;
	pars->av = tab;
	if (c == 0)
		return (-1);
	return (0);
}

int		unalias(t_cmd_tab *cmd)
{
	int		count;
	t_pars	pars;

	count = 0;
	if (pars_unalias(cmd->av + 1, &pars))
		return (1);
	if (ft_cisin(pars.opt, 'a'))
	{
		ft_tabdel(&g_sh.alias);
		g_sh.alias = ft_tabnew(1);
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
