/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:34:05 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/06 16:06:04 by ktlili           ###   ########.fr       */
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
	print_env_tab(g_sh.internal);
	return (0);
}

int ft_unset(t_cmd_tab *cmd)
{
	int i;

	i = 1;
	while (cmd->av[i])
	{
		if ((!(g_sh.export_var = ms_envdel(g_sh.export_var, cmd->av[i])))
			|| (!(g_sh.internal = ms_envdel(g_sh.internal, cmd->av[i]))))
		return(MEMERR);
		i++;
	}
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
	if (!(g_sh.export_var = ms_envaddstr(g_sh.export_var, cmd->av[1], cmd->av[2])))
		return (MEMERR);
	return (0);
}

int	ft_unsetenv(t_cmd_tab *cmd)
{
	int			i;

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
			if (!(g_sh.export_var = ms_envdel(g_sh.export_var, cmd->av[i])))
				return (MEMERR);
			i++;
		}
	}
	return (0);
}

int	ft_echo(t_cmd_tab *cmd)
{
	int i;

	if (cmd->av[1] != NULL)
	{
		i = 1;
		while (cmd->av[i] != NULL)
		{
			ft_printf("%s", cmd->av[i]);
			i++;
			if (cmd->av[i] != NULL)
				ft_printf(" ");
		}
	}
	ft_printf("\n");
	return (0);
}

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
	exit(exit_val);
}
