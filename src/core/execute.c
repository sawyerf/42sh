/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 23:36:07 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/13 01:53:12 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sh_core.h"

static int	setenv_wrapper(t_command *cmd)
{
	int i;

	if (cmd->args[1] == NULL)
	{
		ft_printf("usage: setenv [NAME] [VALUE]\n");
		return (0);
	}
	i = 0;
	if (!valid_env_name(cmd->args[1]))
	{
		putstr_stderr("setenv: variable name is invalid\n");
		return (0);
	}
	while (cmd->args[i] != NULL)
	{
		i++;
		if (i > 3)
		{
			putstr_stderr("setenv: Too many arguments\n");
			return (0);
		}
	}
	return (set_shell_env(cmd->args[1], cmd->args[2]));
}

static int	ft_unsetenv(t_command *cmd)
{
	int			i;
	t_environ	*env;

	if (cmd->args[1] == NULL)
		putstr_stderr("usage: unsetenv [NAME] ..\n");
	else
	{
		i = 0;
		while (cmd->args[i] != NULL)
		{
			env = get_env_node(cmd->args[i]);
			if (env != NULL)
				delete_env_node(env);
			i++;
		}
	}
	return (0);
}

static int	ft_echo(t_command *cmd)
{
	int i;

	if (cmd->args[1] != NULL)
	{
		i = 1;
		while (cmd->args[i] != NULL)
		{
			ft_printf("%s", cmd->args[i]);
			i++;
			if (cmd->args[i] != NULL)
				ft_printf(" ");
		}
	}
	ft_printf("\n");
	return (0);
}

static int	ft_exit(t_command *cmd)
{
	int exit_val;
	int i;

	exit_val = 0;
	i = 0;
	if (cmd->args[1] != NULL)
	{
		if (cmd->args[2] != NULL)
		{
			putstr_stderr("exit: too many arguments\n");
			return (0);
		}
		while (cmd->args[1][i] != 0)
		{
			if (!ft_isdigit(cmd->args[1][i]))
			{
				putstr_stderr("exit: numeric argument required\n");
				return (0);
			}
			i++;
		}
		exit_val = ft_atoi(cmd->args[1]);
	}
	exit(exit_val);
}

int			execute_cmd(t_command *cmd)
{
	static t_builtin	array[7] = {ft_echo, change_dir, setenv_wrapper,
							ft_unsetenv, ft_env, ft_exit};
	static	char		*builtins[] = {"echo", "cd", "setenv", "unsetenv",
							"env", "exit", NULL};
	int					i;

	if (cmd->args[0] == NULL)
		return (0);
	cmd->process_env = lst_to_tab(*g_environ, 0);
	if ((cmd->process_env == NULL)
		|| (expand_tokens(cmd->args) == MEMERR))
		return (MEMERR);
	if (cmd->args[0] == NULL)
		return (0);
	if ((i = ft_cmptab(builtins, cmd->args[0])) != -1)
		return (array[i](cmd));
	else
		return (spawn_bin(cmd));
	return (0);
}
