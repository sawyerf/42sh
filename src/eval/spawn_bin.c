/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:11:09 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/01 19:08:58 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

void		exec_error(int errnum, char *str)
{
	if (errnum == BIN_NO_PATH)
		putstr_stderr("21sh: PATH not set");
	else if (errnum == CMD_NOT_FOUND)
		putstr_stderr("21sh: command not found: ");
	else if (errnum == BIN_PERM_DENY)
		putstr_stderr("21sh: permission denied: ");
	else if (errnum == BIN_NOT_FOUND)
		putstr_stderr("21sh: no such file or directory: ");
	else if (errnum == BIN_EXEC_ERR)
		putstr_stderr("21sh: exec error: ");
	else if (errnum == BIN_IS_DIR)
		putstr_stderr("21sh: is a directory: ");
	if (str != NULL)
		putstr_stderr(str);
	putstr_stderr("\n");
}

int			bin_perm(char *path)
{
	struct stat target;

	if (stat(path, &target) != 0)
		return (BIN_NOT_FOUND);
	if (!S_ISREG(target.st_mode))
	{
		if (S_ISDIR(target.st_mode))
				return (BIN_IS_DIR);
		return (BIN_PERM_DENY);
	}
	if (access(path, X_OK) != 0)
		return (BIN_PERM_DENY);
	return (0);
}

int			handle_full_path(char *cmd_name)
{
	int ret;

	if ((ret = bin_perm(cmd_name)) != 0)
	{
		exec_error(ret, cmd_name);
		return (ACCERR);
	}
	return (0);
}


static int		execve_wrap(t_cmd_tab *cmd)
{	
	char	*path;
	int		ret;

	if (ft_ispath(cmd->av[0]))
	{
		if (handle_full_path(cmd->av[0]) != 0)
			return (0);
		if ((cmd->full_path = ft_strdup(cmd->av[0])) == NULL)
			return (MEMERR);
	}
	else 
	{
		path = get_env_value("PATH");
		if (bin_pathfinder(cmd, path) == MEMERR)
			return (MEMERR);
		if (cmd->full_path == NULL) /* case bin not found or no perm*/
			return (0);	/* maybe exit ?*/
	}
	ret = execve(cmd->full_path, cmd->av, cmd->process_env); 
	putstr_stderr("21sh: bad file format\n");
	return (ret);
}

int		execute_command(t_cmd_tab *cmd)
{
	/* 1- assign variables.
	 * 2- craft env
	 * 3- if builtin call builtin, job is done
	 * 3- proceed to execve wrap
	 */
	/*
	 * setenv and unsetenv are broken because we fork
	 * */
	static t_builtin	array[7] = {ft_echo, change_dir, setenv_wrapper,
							ft_unsetenv, ft_env, ft_exit};
	static	char		*builtins[] = {"echo", "cd", "setenv", "unsetenv",
							"env", "exit", NULL};
	int					i;

	if (cmd->av[0] == NULL)
		return (0);
	cmd->process_env = lst_to_tab(*g_environ, 0);
	if (cmd->process_env == NULL)
		return (MEMERR);
	if ((i = ft_cmptab(builtins, cmd->av[0])) != -1)
		return (array[i](cmd)); /* exit status should be handeled in cmd_tab struct*/
	else
		return (execve_wrap(cmd));
}

int		spawn_command(t_cmd_tab *cmd)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		return (MEMERR);
	if (pid == 0)
	{
		execute_command(cmd);
		exit(1); /* handle errors here*/
	}
	wait(NULL);
	return (0);

}
