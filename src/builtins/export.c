/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 15:58:01 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/04 17:17:59 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "sh_core.h"

extern t_sh	g_sh;


int		parser_tkopt(char *opt, char *arg, char *in)
{
	int		i;
	char	c;

	i = 1;
	c = 0;
	if (arg[0] != '-')
		return (0);
	if (!ft_strcmp("--", arg))
		return ('-');
	while (arg[i])
	{
		c = arg[i];
		if (!ft_cisin(in, arg[i]))
		{
			if (ft_cisin(opt, arg[i]))
				ft_strncat(in, arg + i, 1);
			else
				return (-1);
		}
		i++;
	}
	return (c);
}

char	**ch_parser(char **av)
{
	char	c;
	char	opt[2];

	opt[0] = 0;
	while (*av)
	{
		c = parser_tkopt("p", *av, opt);
		if (c == '-' || c == 0 || c == -1)
		{
			if (c == '-')
				av++;
			else if (c == -1)
				ft_dprintf(2, "export: illegal option `%s'\n", *av);
			return (av);
		}
		av++;
	}
	return (av);
}

void	print_export(char **env)
{
	if (!env)
		return ;
	while (*env)
	{
		ft_printf("export %s\n", *env);
		env++;
	}
}

int		export(t_cmd_tab *cmd)
{
	char	**av;

	av = ch_parser(cmd->av + 1);
	if (!*av)
	{
		print_export(g_sh.env);
		return (0);
	}
	while (*av)
	{
		if (ft_cisin(*av, '='))
		{
			if (valid_alias(*av))
			{
				g_sh.env = csetenv(g_sh.env, *av);
				if (varchr(g_sh.local, *av))
					g_sh.local = csetenv(g_sh.local, *av);
			}
			else 
				ft_dprintf(2, "export: `%s': invalid alias name\n", *av);
		}
		else if (varchr(g_sh.local, *av))
			g_sh.env = envaddstr(g_sh.env, *av, varchr(g_sh.local, *av));
		av++;
	}
	return (0);
}
