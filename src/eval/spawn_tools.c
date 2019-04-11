/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 19:20:53 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/11 23:03:57 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

void	free_cmd_tab(t_cmd_tab *cmd)
{
	if (!cmd)
		return ;
	if (cmd->full_path)
		ft_strdel(&cmd->full_path);
	if (cmd->av)
		free_tab(cmd->av);
	if (cmd->process_env)
		free_tab(cmd->process_env);
	if (cmd->assign_lst)
		free_tab(cmd->assign_lst);
	free(cmd);
}

void	free_cmd_tab_lst(t_cmd_tab *start)
{
	t_cmd_tab	*tmp;

	while (start)
	{
		tmp = start->next;
		free_cmd_tab(start);
		start = tmp;
	}
}

void	exec_error(int errnum, char *str)
{
	if (errnum == BIN_NO_PATH)
		putstr_stderr("21sh: PATH not set: ");
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

int		bin_perm(char *path)
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

int		handle_perm(char *cmd_name)
{
	int ret;

	if ((ret = bin_perm(cmd_name)) != 0)
		return (ret);
	return (0);
}
