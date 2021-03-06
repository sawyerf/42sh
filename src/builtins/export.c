/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 15:58:01 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/24 17:45:36 by apeyret          ###   ########.fr       */
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

int		cexport(char *var)
{
	if (!var)
		return (1);
	if (ft_cisin(var, '='))
	{
		if (valid_alias(var))
		{
			csetenv(&g_sh.env, var);
			if (varchr(g_sh.local, var))
				csetenv(&g_sh.local, var);
		}
		else
			return (1);
	}
	else if (varchr(g_sh.local, var))
		envaddstr(&g_sh.env, var, varchr(g_sh.local, var));
	return (0);
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
		if (cexport(*av))
			ft_dprintf(2, "export: `%s': invalid alias name\n", *av);
		av++;
	}
	return (0);
}
