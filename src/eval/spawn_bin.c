/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:11:09 by ktlili            #+#    #+#             */
/*   Updated: 2019/03/19 13:30:21 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"
#include "readline.h" //this should be resolved differently

/* execve_wrap is always inside a fork*/

void	restore_fd(t_list *to_close)
{
	while (to_close)
	{
		close(*((int*)(to_close->content)));
		to_close = to_close->next;
	}
	dup2(FDSAVEIN, STDIN_FILENO);
	dup2(FDSAVEOUT, STDOUT_FILENO);
	dup2(FDSAVEERR, STDERR_FILENO);
}

void close_save(void)
{
	close(FDSAVEIN);
	close(FDSAVEOUT);
	close(FDSAVEERR);
}

static int		execve_wrap(t_cmd_tab *cmd)
{	
	char	*path;
	int		ret = 50;

	close_save();
/*	if ((ret = handle_redir(cmd->redir_lst, NULL))) // this has to change we have more err
		exit(1);*/
	if (ft_ispath(cmd->av[0]))
	{
		if (handle_perm(cmd->av[0]) != 0)
			exit_wrap (ACCERR, cmd);
		if ((cmd->full_path = ft_strdup(cmd->av[0])) == NULL)
			exit_wrap(MEMERR, cmd);
	}
	else if (!cmd->full_path) //f launched with env, builtin have already set the full path 
	{
		if (!(path = get_process_env("PATH", cmd->process_env)))
			path = get_env_value("PATH");
		if (ht_getvalue(path, cmd) == MEMERR)
			return (MEMERR);
		if (!cmd->full_path)
			exit_wrap (127, cmd);
	}
//	ret = execve(cmd->full_path, cmd->av, cmd->process_env); 
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
}


int		is_builtin(t_cmd_tab *cmd)
{
	static t_builtin	array[] = {ft_echo, change_dir, setenv_wrapper,
							ft_unsetenv, ft_env, ft_exit, ft_set, ft_unset, fc, hash}; //, hash};
	static	char		*builtins[] = {"echo", "cd", "setenv", "unsetenv",
							"env", "exit", "set", "unset", "fc", "hash", NULL};
	int					i;
	//int					ret;
	t_list				*save_head;

	save_head = NULL;
	if ((i = ft_cmptab(builtins, cmd->av[0])) != -1)
	{
/*		if ((ret = handle_redir(cmd->redir_lst, &save_head))) // this has to change we have more err
			return(0);*/
		cmd->process_env = craft_env(g_sh.env, cmd->assign_lst);
		if (cmd->process_env == NULL)
			return (MEMERR);
		cmd->exit_status = array[i](cmd);
		restore_fd(save_head);
		return (0);
	}
	return (-1);
}

int		spawn_in_pipe(t_cmd_tab *cmd)
{
	int ret;

	if (cmd->av[0] == NULL)
		return (0);
	if ((ret = is_builtin(cmd)) == 0)
	{
		free_cmd_tab(cmd);
		return (0);
	}
	else if (ret == MEMERR)
		return (MEMERR);
	else
	{
		if (!(cmd->process_env = craft_env(g_sh.env, cmd->assign_lst)))
			return (MEMERR);
		return (execve_wrap(cmd));
	}
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

int		spawn_command(t_cmd_tab *cmd)
{
	pid_t 		pid;
	int			ret;

	if (cmd->av[0] == NULL)
		return (assign_to_shell(cmd));
	if ((ret = is_builtin(cmd)) == 0)
		return (0);
	else if (ret == MEMERR)
		return (MEMERR);
	pid = fork();
	if (pid == -1)
		return (MEMERR);
	if (pid == 0)
	{
		if ((!cmd->process_env) 
				&& (!(cmd->process_env = craft_env(g_sh.env, cmd->assign_lst))))
			return (MEMERR);
		execve_wrap(cmd);
		exit_wrap(1, cmd); /* handle errors here*/
	}
	wait_wrapper(cmd, pid);
	return (0);
}
