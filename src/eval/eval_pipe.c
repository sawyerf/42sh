/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 11:48:18 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/04 22:33:05 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

int	pipe_recursion(t_cmd_tab *to, t_cmd_tab *from)
{
	int pipes[2];
	int pid;

	if (pipe(pipes) != 0)
		return (PIPEFAIL);
	if ((pid = fork()) == -1)
		return (MEMERR);
	if (pid == 0)
	{
		if (to)
		{
			dup2(pipes[1], STDOUT_FILENO);
			close(pipes[0]);
		}
		spawn_in_pipe(from);
		exit(0);
	}
	if (to)
	{
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[1]);
		return (pipe_recursion(to->next, to));
	}
	wait_wrapper(from, pid);
	return (from->exit_status);
}

int	eval_pipe(t_cmd_tab *cmd)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		ret = pipe_recursion(cmd->next, cmd);
		exit(ret);
	}
	wait_wrapper(cmd, pid);
	return (0);
}

int	exec_pipeline(t_ast_node *tree)
{
	t_cmd_tab	*cmd_tab;
	int			ret;

	ret = 0;
	if (!(cmd_tab = expand_pipeline(tree->pipeline)))
		return (MEMERR);
	if (cmd_tab->next)
		ret = eval_pipe(cmd_tab);
	else
		ret = spawn_command(cmd_tab);
	tree->exit_status = cmd_tab->exit_status;
	g_sh.status = tree->exit_status;
	free_cmd_tab_lst(cmd_tab);
	return (ret);
}
