/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:11:09 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/19 16:55:34 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"
#include "readline.h"

/* execve_wrap is always inside a fork*/
static int		execve_wrap(t_cmd_tab *cmd)
{	
	char	*path;
	int		ret;

	cmd->process_env = craft_env(g_sh.export_var, cmd->assign_lst);
	if (cmd->process_env == NULL)
		return (MEMERR);
	if ((ret = handle_redir(cmd->redir_lst))) // this has to change we have more err
		exit(1);
	if (ft_ispath(cmd->av[0]))
	{
		if (handle_perm(cmd->av[0]) != 0)
			exit_wrap (ACCERR, cmd);
		if ((cmd->full_path = ft_strdup(cmd->av[0])) == NULL)
			exit_wrap(MEMERR, cmd);
	}
	else 
	{
		path = get_process_env("PATH", cmd->process_env);
		if (ht_getvalue(path, cmd) == MEMERR)
			return (MEMERR);
		if (!cmd->full_path)
			exit_wrap (127, cmd);
	}
	ret = execve(cmd->full_path, cmd->av, cmd->process_env); 
	putstr_stderr("21sh: bad file format\n");
	exit_wrap(ret, cmd);
	return (0);
}


void	wait_wrapper(t_cmd_tab *cmd, pid_t pid)
{
	int		wstatus;

	waitpid(pid, &wstatus, 0);	
	cmd->exit_signal = -1;
	cmd->exit_status = -1;
	if (WIFEXITED(wstatus))
	{
		cmd->exit_status = (int)WEXITSTATUS(wstatus);
	}
	else if (WIFSIGNALED(wstatus))
	{
		cmd->exit_signal = WTERMSIG(wstatus);
	}
	//ft_printf("%s exiting with status %d\n", cmd->av[0], cmd->exit_status);
}


t_bool		is_builtin(t_cmd_tab *cmd)
{
	static t_builtin	array[9] = {ft_echo, change_dir, setenv_wrapper,
							ft_unsetenv, ft_env, ft_exit, ft_set, ft_unset};
	static	char		*builtins[] = {"echo", "cd", "setenv", "unsetenv",
							"env", "exit", "set", "unset", NULL};
	int					i;

	if ((i = ft_cmptab(builtins, cmd->av[0])) != -1)
	{
		cmd->process_env = craft_env(ft_tabdup(g_sh.export_var), cmd->assign_lst);
		if (cmd->process_env == NULL)
			return (MEMERR);
		cmd->exit_status = array[i](cmd);
		ft_printf("BUILTIN:%s exited with status %d\n", cmd->av[0], cmd->exit_status);
		return (FT_TRUE);
	}
	return (FT_FALSE);
}

int		spawn_in_pipe(t_cmd_tab *cmd)
{
	if (cmd->av[0] == NULL)
		return (0);
	if (is_builtin(cmd) == FT_TRUE)
	{
		free_cmd_tab(cmd);
		return (0);
	}
	else
		return (execve_wrap(cmd));
}

static int assign_to_shell(t_cmd_tab *cmd)
{
	int i;
	int	len;
	char	c;

	i = 0;
	while (cmd->assign_lst[i])
	{
		len = ft_strchr(cmd->assign_lst[i], '=') - cmd->assign_lst[i] + 1;
		c = cmd->assign_lst[i][len];
		cmd->assign_lst[i][len] = 0;
		if (ms_varchr(g_sh.export_var, cmd->assign_lst[i]))
		{
			cmd->assign_lst[i][len] = c;
			g_sh.export_var = ms_csetenv(g_sh.export_var, cmd->assign_lst[i]);
		}
		else
		{
			cmd->assign_lst[i][len] = c;
			g_sh.internal = ms_csetenv(g_sh.internal, cmd->assign_lst[i]);
		}
		if ((!g_sh.internal) || (!g_sh.export_var))
			return (MEMERR);
		i++;	
	}
	return (0);
}

int		spawn_command(t_cmd_tab *cmd)
{
	pid_t 		pid;

	if (cmd->av[0] == NULL)
		return (assign_to_shell(cmd));
	if (is_builtin(cmd) == FT_TRUE)
		return (0);
	pid = fork();
	if (pid == -1)
		return (MEMERR);
	if (pid == 0)
	{
		execve_wrap(cmd);
		exit_wrap(1, cmd); /* handle errors here*/
	}
	wait_wrapper(cmd, pid);
	return (0);
}
