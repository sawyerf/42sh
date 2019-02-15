/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 13:58:14 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/15 21:48:49 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

static char		**construct_env(t_cmd_tab *cmd, char opt, int count)
{
	char		**new_env;

	count = count - g_optind;
	if (opt == 'i')
		new_env = NULL;
	else
		new_env = ft_tabdup(g_sh_state.export_var);
	if ((new_env == NULL)
			|| (append_tab(new_env, cmd->av + g_optind, count) == MEMERR))
		return (NULL);
	return (new_env);
}

static int		spawn_new_env(char **args, char **new_env)
{
	t_command	*new_cmd;
	int			ret = 5;

	new_cmd = new_cmd_node(args);
	if (new_cmd == NULL)
		return (MEMERR);
	new_cmd->process_env = new_env;
//	ret = spawn_bin(new_cmd);
	free_cmdlst(new_cmd);
	return (ret);
}

static char		env_parseopt(char **args)
{
	int		flag;
	char	opt;

	flag = 0;
	g_optind = 1;
	opt = 0;
	while ((flag = ft_getopt(args, "i")) != -1)
	{
		opt = (char)flag;
		if (opt == '?')
		{
			ft_printf("usage: env [-i] [NAME=VAR] .. [BIN]\n");
			break ;
		}
	}
	return (opt);
}

int				ft_env(t_cmd_tab *cmd)
{
	int			count;
	char		**new_env;
	char		opt;
	int			ret;

	ret = 0;
	if ((opt = env_parseopt(cmd->av)) == '?')
		return (0);
	count = g_optind;
	while ((cmd->av[count] != NULL) && (valid_env_var(cmd->av[count])))
		count++;
	if ((new_env = construct_env(cmd, opt, count)) == NULL)
		return (MEMERR);
	if (cmd->av[count] == NULL)
	{
		print_env_tab(new_env);
		free_tab(new_env);
	}
	else
		ret = spawn_new_env(cmd->av + count, new_env);
	return (ret);
}
