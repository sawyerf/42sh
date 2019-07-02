/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 19:59:07 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/02 19:10:58 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

extern t_sh g_sh;

int			extract_last_tok(t_cmd_tab *pipeln)
{
	int i;

	i = 0;
	while (pipeln->next)
		pipeln = pipeln->next;
	if (!pipeln->av[0])
		return (0);
	while (pipeln->av[i + 1])
		i++;
	envaddstr(&g_sh.env, "_", pipeln->av[i]);
	return (0);
}

static void	job_exit_code(t_ast_node *tree, t_job *job)
{
	if (job->builtin_exit != -1)
		tree->exit_status = job->builtin_exit;
	else
		tree->exit_status = (int)WEXITSTATUS(job->status);
	del_job(job);
}

int			launch_pipe(t_ast_node *tree, t_job *job)
{
	t_cmd_tab	*cmd_tab;
	int			ret;

	if ((!job) && (!(job = make_job(1))))
		return (MEMERR);
	if (g_sh.mode == NONINTERACTIVE)
		job->pgid = getpgrp();
	if ((!(job->cmd_ln))
			&& (!(job->cmd_ln = make_cmdline(tree->start, tree->end, 0))))
		return (MEMERR);
	if (!(cmd_tab = expand_pipeline(tree->pipeline)))
		return (MEMERR);
	if ((job->fg) && (extract_last_tok(cmd_tab)))
		return (MEMERR);
	if (cmd_tab->next)
		ret = eval_pipe(cmd_tab, job);
	else
		ret = launch_command(cmd_tab, job);
	if (WIFEXITED(job->status) || (job->builtin_exit != -1))
		job_exit_code(tree, job);
	g_sh.status = tree->exit_status;
	free_cmd_tab_lst(cmd_tab);
	return (ret);
}
