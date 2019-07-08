/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_subshell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 16:08:31 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 16:24:02 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

int	background_fork(pid_t pid, t_job *job, t_ast_node *t)
{
	if (setpgid_wrap(pid, job) == -1)
		exit_wrap(MEMERR, NULL);
	g_sh.mode = NONINTERACTIVE;
	reset_sig();
	eval_tree(t->left);
	waitpid(job->pgid, NULL, WUNTRACED);
	waitpid(WAIT_ANY, NULL, 0);
	exit_wrap(0, NULL);
	return (0);
}

int	background_subshell(t_ast_node *tree)
{
	t_job	*job;
	pid_t	pid;

	if (!(job = make_job(0))
			|| (!(job->cmd_ln = make_cmdline(tree->start, tree->end, 1))))
		return (MEMERR);
	if ((pid = fork()) == -1)
		return (MEMERR);
	if (pid == 0)
		background_fork(pid, job, tree);
	if (setpgid_wrap(pid, job) == -1)
		ft_dprintf(STDERR_FILENO, "42sh: setpgid fail for %d\n", pid);
	register_job(job);
	ft_dprintf(STDERR_FILENO, "[%d] %d\n", job->job_id, job->pgid);
	tcgetattr(STDIN_FILENO, &(job->save_tio));
	g_sh.lastback = job->pgid;
	g_sh.previous_j = g_sh.current_j;
	g_sh.current_j = job;
	return (0);
}
