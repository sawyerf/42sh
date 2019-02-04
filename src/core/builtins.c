/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:34:05 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/01 19:09:07 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
/* replace t_cmd_tab with new cmd struct
 *
 *
 * */
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
	return (set_shell_env(cmd->av[1], cmd->av[2]));
}

int	ft_unsetenv(t_cmd_tab *cmd)
{
	int			i;
	t_environ	*env;

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
			env = get_env_node(cmd->av[i]);
			if (env != NULL)
				delete_env_node(env);
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
