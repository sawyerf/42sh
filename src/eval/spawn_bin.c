/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:11:09 by ktlili            #+#    #+#             */
/*   Updated: 2019/06/27 16:42:02 by ktlili           ###   ########.fr       */
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
	reset_sig();
	ret = execve(cmd->full_path, cmd->av, cmd->process_env);
	ft_dprintf(2, "42sh: bad file format\n");
	exit_wrap(ret, cmd);
	return (0);
}

int				spawn_in_pipe(t_cmd_tab *cmd)
{
	int ret;

	if ((ret = pre_execution(cmd)) == MEMERR)
		exit_wrap(MEMERR, cmd);
	else if ((ret == BUILTIN) || (ret == BUILTIN_FAIL))
		exit_wrap(cmd->exit_status, cmd);
	return (execve_wrap(cmd));
}
/*
int				exec_candidate(t_cmd_tab *cmd)
{
	if !(cmd->full_path) && ()
}
*/
int				launch_command(t_cmd_tab *cmd, t_job *job)
{
	pid_t	pid;
	int		ret;

	if ((ret = pre_execution(cmd)) == MEMERR)
		return (MEMERR);
	else if (ret == BUILTIN_FAIL)
		return (0);
	if (ret != BUILTIN)// && exec_candidate(cmd))
	{
		pid = fork();
		if (pid == -1)
			return (MEMERR);
		if (pid == 0) 
		{
			if ((job) && (g_sh.mode == INTERACTIVE))
			{
				if ((setpgid_wrap(pid, job) == -1))
					exit_wrap(MEMERR, cmd);
				if (job->fg)
					tcsetpgrp(STDIN_FILENO, job->pgid);
			}
			execve_wrap(cmd);
		}
		if ((g_sh.mode == INTERACTIVE) && (job) && (!job->pgid) 
			&& (setpgid_wrap(pid, job) == -1))
		return (MEMERR);		
		/* builtins freeze when there are stopped jobs*/
		if ((g_sh.mode != INTERACTIVE))
			wait_job(job);
		else if ((job) && (job->fg))
			fg_job( job, 0);
		else
			bg_job(job, 0);	
	}
	else
	{
		job->builtin_exit = cmd->exit_status;
		register_job(job); //this is ugly
	}
	return (0);
}

