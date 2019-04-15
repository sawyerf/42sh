/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 20:19:10 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/15 20:24:01 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"
#include "hashtable.h"
#include "builtins.h"

int				is_builtin(t_cmd_tab *cmd)
{
	static t_builtin	array[] = {ft_echo, change_dir, setenv_wrapper,
				ft_unsetenv, ft_env, ft_exit, ft_set, ft_unset, fc, hash};
	static	char		*builtins[] = {"echo", "cd", "setenv", "unsetenv",
				"env", "exit", "set", "unset", "fc", "hash", NULL};
	int					i;
	int					ret;
	t_list				*save_head;

	save_head = NULL;
	if ((i = ft_cmptab(builtins, cmd->av[0])) != -1)
	{
		if ((ret = handle_redir(cmd->redir_lst, &save_head)))
		{
			ft_lstdel(&save_head);
			return (BUILTIN_FAIL);
		}
		cmd->process_env = craft_env(g_sh.env, cmd->assign_lst);
		if (cmd->process_env == NULL)
			return (MEMERR);
		cmd->exit_status = array[i](cmd);
		restore_fd(save_head);
		ft_lstdel(&save_head);
		return (0);
	}
	return (-1);
}

static int		assign_to_shell(t_cmd_tab *cmd)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	while (cmd->assign_lst[i])
	{
		len = ft_strchr(cmd->assign_lst[i], '=') - cmd->assign_lst[i] + 1;
		c = cmd->assign_lst[i][len];
		cmd->assign_lst[i][len] = 0;
		if (varchr(g_sh.env, cmd->assign_lst[i]))
		{
			cmd->assign_lst[i][len] = c;
			g_sh.env = csetenv(g_sh.env, cmd->assign_lst[i]);
		}
		else
		{
			cmd->assign_lst[i][len] = c;
			g_sh.local = csetenv(g_sh.local, cmd->assign_lst[i]);
		}
		if ((!g_sh.local) || (!g_sh.env))
			return (MEMERR);
		i++;
	}
	return (0);
}

int				pathfinder(t_cmd_tab *cmd)
{
	char	*path;
	int		ret;
	static char *curr_dir = "./";

	if (!(path = get_process_env("PATH", cmd->process_env)))
		path = get_env_value("PATH");
	if ((path) && (*path == 0))
		path = curr_dir;
	if ((ret = ht_spawnbin(path, cmd)))
	{
		if (cmd->full_path)
			ft_strdel(&(cmd->full_path));
		br_print(ret, cmd);
		if (!cmd->redir_lst)
			return (ret);
	}
	return (0);
}

int				pre_execution(t_cmd_tab *cmd)
{
	int		ret;

	ret = 0;
	if (cmd->av[0] == NULL)
		if (assign_to_shell(cmd))
			return (MEMERR);
	if ((!cmd->full_path) && (cmd->av[0]) && ((ret = is_builtin(cmd)) == 0))
		return (BUILTIN);
	if ((ret == MEMERR) || (ret == BUILTIN_FAIL))
		return (ret);
	if ((!cmd->process_env)
			&& (!(cmd->process_env = craft_env(g_sh.env, cmd->assign_lst))))
		return (MEMERR);
	if (!(cmd->full_path) && (cmd->av[0]))
	{
		if ((ret = pathfinder(cmd)))
			return (ret);
	}
	return (0);
}
