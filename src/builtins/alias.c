/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:57:28 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/24 17:27:07 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "sh_core.h"

extern t_sh	g_sh;

int		valid_alias(char *s)
{
	while (*s)
	{
		if (*s == '=')
			return (1);
		else if (!ft_isdigit(*s) && !ft_isalpha(*s)
					&& ft_cisin("$()&|;/\"'\\`<> \n\r\t", *s))
			return (0);
		s++;
	}
	return (0);
}

int		alias(t_cmd_tab *cmd)
{
	int		count;

	count = -1;
	if (!cmd->av[1])
		print_env_tab(g_sh.alias);
	while (cmd->av[++count])
	{
		if (ft_cisin(cmd->av[count], '='))
		{
			if (ft_tablen(g_sh.alias) > 1024)
				ft_dprintf(2, "alias: too much alias. Please stop!\n");
			else if (valid_alias(cmd->av[count]))
			{
				if (csetenv(&g_sh.alias, cmd->av[count]))
					return (MEMERR);
			}
			else
				ft_dprintf(2, "alias: `%s': invalid alias name\n",
						cmd->av[count]);
		}
		else
		{
			if (varchr(g_sh.alias, cmd->av[count]))
				ft_printf("%s='%s'\n", cmd->av[count],
							varchr(g_sh.alias, cmd->av[count]));
		}
	}
	return (0);
}
