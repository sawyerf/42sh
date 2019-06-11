/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:11:09 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/12 16:44:34 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"
#include "hashtable.h"
#include "builtins.h"

static int		execve_wrap(t_cmd_tab *cmd)
{
	int		ret;

	close_save();
	if ((ret = handle_redir(cmd->redir_lst, NULL)))
		exit(1);
	if ((cmd->av[0]) && (ft_cisin(cmd->av[0], '/')))
	{
		if (handle_perm(cmd->av[0]) != 0)
			exit_wrap(ACCERR, cmd);
		if ((cmd->full_path = ft_strdup(cmd->av[0])) == NULL)
			exit_wrap(MEMERR, cmd);
	}
	if ((!cmd->full_path))
		exit_wrap(CMD_NOT_FOUND, cmd);
	ret = execve(cmd->full_path, cmd->av, cmd->process_env);
	ft_dprintf(2, "21sh: bad file format\n");
	exit_wrap(ret, cmd);
	return (0);
}

void			wait_wrapper(t_cmd_tab *cmd, pid_t pid)
{
	int	wstatus;

	waitpid(pid, &wstatus, 0);
	cmd->exit_signal = -1;
	cmd->exit_status = -1;
	if (WIFEXITED(wstatus))
		cmd->exit_status = (int)WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		cmd->exit_signal = WTERMSIG(wstatus);
}

int				spawn_in_pipe(t_cmd_tab *cmd)
{
	int ret;

	if ((ret = pre_execution(cmd)) == MEMERR)
		return (MEMERR);
	else if ((ret == BUILTIN) || (ret == BUILTIN_FAIL))
		return (0);
	return (execve_wrap(cmd));
}

int				spawn_command(t_cmd_tab *cmd)
{
	pid_t	pid;
	int		ret;

	if ((ret = pre_execution(cmd)) == MEMERR)
		return (MEMERR);
	else if ((ret == BUILTIN) || (ret == BUILTIN_FAIL))
		return (0);
	pid = fork();
	if (pid == -1)
		return (MEMERR);
	if (pid == 0)
		execve_wrap(cmd);
	wait_wrapper(cmd, pid);
	return (0);
}
