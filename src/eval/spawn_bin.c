/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:11:09 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/12 22:33:21 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sh_core.h"

void		exec_error(int errnum, char *str)
{
	if (errnum == 1)
		putstr_stderr("21sh: PATH not set");
	else if (errnum == 2)
		putstr_stderr("21sh: command not found: ");
	else if (errnum == 3)
		putstr_stderr("21sh: permission denied: ");
	else if (errnum == 4)
		putstr_stderr("21sh: no such file or directory: ");
	else if (errnum == 5)
		putstr_stderr("21sh: exec error: ");
	if (str != NULL)
		putstr_stderr(str);
	putstr_stderr("\n");
}

int			bin_perm(char *path)
{
	struct stat target;

	if (stat(path, &target) != 0)
		return (4);
	if (!S_ISREG(target.st_mode))
		return (3);
	if (access(path, X_OK) != 0)
		return (3);
	return (0);
}

static int	spawner(t_cmd_tab *cmd, char *binpath)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		return (MEMERR);
	if (pid == 0)
	{
		execve(binpath, cmd->av, cmd->process_env);
		putstr_stderr("21sh: bad file format\n");
		exit(1);
	}
	if (pid > 0)
	{
		wait(NULL);
	}
	return (0);
}

int			handle_fullpath(char *cmd_name, char **full_path)
{
	int ret;

	if ((ret = bin_perm(cmd_name)) != 0)
	{
		exec_error(ret, cmd_name);
		return (ACCERR);
	}
	return (0);
}

int			spawn_bin(t_cmd_tab *cmd)
{
	char	*full_path;
	char	*bin_path;
	int		ret;

	full_path = NULL;
	if ((ft_ispath(cmd->av[0]))
			&& ((ret = handle_fullpath(cmd, &full_path)) != 0))
		return (ret);
	else if (!ft_ispath(cmd->av[0]))
	{
		bin_path = tab_get_value("PATH", cmd->process_env);
		if (bin_path == NULL)
			bin_path = get_env_value("PATH");
		full_path = searchbin(cmd->av[0], bin_path);
		if (full_path == NULL)
			return (0);
	}
	ret = spawner(cmd, full_path);
	free(full_path);
	return (ret);
}

char *handle_full_path(char *cmd_name)
{
	char	*full_path;
	char	*bin_path;
	int		ret;

	full_path = NULL;
	if (ft_ispath(cmd_name))
	{
		if (full_path = ft_strdup(cmd_name) == NULL)
			return (NULL);
	}
	else 
	{
		bin_path = tab_get_value("PATH", cmd->process_env);
		if (bin_path == NULL)
			bin_path = get_env_value("PATH");
		full_path = searchbin(cmd_name, bin_path);
		if (full_path == NULL)
			return (NULL);
	}
	return (full_path);
}
