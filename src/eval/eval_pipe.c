/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 11:48:18 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/04 15:41:26 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"
/*
int		pipe_callback(t_cmd_tab *to, t_cmd_tab *from)
{
	int pipes[2];
	int pid;

	if (pipe(pipes) != 0)
		return (PIPEFAIL);
	pid = fork();
	if (pid == -1)
		return (-1); //should be exec error
	if (pid == 0)
	{
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		if (from->next != NULL)
			pipe_callback(from, from->next);
		execute_command(from);
		exit(0);
	}
	dup2(pipes[0], STDIN_FILENO);
	close(pipes[1]);
	execute_command(to);
	wait (NULL);
	return (0);
}*/

int	pipe_recursion(t_cmd_tab *to, t_cmd_tab *from)
{
	int pipes[2];
	int pid;

	if (pipe(pipes) != 0)
		return (PIPEFAIL);
	pid = fork();
	if (pid == -1)
		return (-1); //should be exec error
	if (pid == 0)
	{
		if (to)
		{
			dup2(pipes[1], STDOUT_FILENO);
			close(pipes[0]);
		}
		execute_command(from);
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
	pid_t pid;
	int ret;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		ret = pipe_recursion(cmd->next, cmd);
		exit(ret);
	}
	wait_wrapper(cmd, pid);
	ft_printf("pipe exiting with status %d\n", cmd->exit_status);
	return (0);
}

void	free_cmd_tab(t_cmd_tab *cmd)
{
	if (!cmd)
		return;
	if (cmd->full_path)
		free(cmd->full_path);
	if (cmd->av)
	{
		free_tab(cmd->av);
	}
//	if (cmd->process_env)
//		free_tab(cmd->process_env);
	if (cmd->assign_lst)
		free_tab(cmd->assign_lst);
	free(cmd);
}
void	free_cmd_tab_lst(t_cmd_tab *start)
{
	t_cmd_tab *tmp;

	while (start)
	{
		tmp = start->next;
		free_cmd_tab(start);
		start = tmp;
	}
}
int	exec_pipeline(t_ast_node *tree)
{
	t_cmd_tab 	*cmd_tab;
	int			ret;

	if (!(cmd_tab = expand_pipeline(tree->pipeline)))
		return (MEMERR);
	if (cmd_tab->next)
		ret = eval_pipe(cmd_tab);
	else 
		ret = spawn_command(cmd_tab);
	if (ret)
		return (ret);
	tree->exit_status = cmd_tab->exit_status;
	free_cmd_tab_lst(cmd_tab);
	return (0);
}

