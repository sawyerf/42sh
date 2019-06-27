/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:24:20 by ktlili            #+#    #+#             */
/*   Updated: 2019/06/27 19:45:09 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		refresh_jobs(void)
{
	t_job *j;
	pid_t chld;

	j = g_sh.job_lst;
	while (j)
	{
		chld = waitpid(-(j->pgid), &(j->status),
				WUNTRACED | WNOHANG | WCONTINUED);
		if (WIFSIGNALED(j->status))
			j->completed = 1;
		if ((chld > 0) && (WIFEXITED(j->status)))
			j->completed = 1;
		if (WIFSTOPPED(j->status))
			j->stopped = 1;
		else
			j->stopped = 0;
		j = j->next;
	}
	return (0);
}

/*
** no malloc, null ret for inexistant job
*/

int		invalid_opt(void)
{
	ft_dprintf(STDERR_FILENO, "42sh: jobs: invalid option");
	ft_dprintf(STDERR_FILENO, "jobs : usage : jobs [-ln] [jobspec]\n");
	return (0);
}

int		do_it(t_job *arg_job, t_job_print jobs_printer, t_cmd_tab *cmd, int i)
{
	if (!(arg_job = jobs_conversion(cmd->av[i])))
		ft_dprintf(STDERR_FILENO, "42sh: jobs: '%s': no such job\n",
					cmd->av[i]);
	else
	{
		jobs_printer(arg_job);
		arg_job->notified = 1;
	}
	return (1);
}

int		jobs(t_cmd_tab *cmd)
{
	t_job_print	jobs_printer;
	t_job		*arg_job;
	char		opt;
	int			i;

	arg_job = NULL;
	opt = 'l';
	g_optind = 1;
	while ((i = ft_getopt(cmd->av, "lp")) != -1)
	{
		opt = (char)i;
		if (opt == '?')
			return (invalid_opt());
	}
	refresh_jobs();
	jobs_printer = jobs_print_p;
	if (opt == 'l')
		jobs_printer = jobs_print_l;
	i = g_optind;
	if (!(cmd->av[i]))
		return (jobs_print_all(jobs_printer));
	while (cmd->av[i])
		i += do_it(arg_job, jobs_printer, cmd, i);
	return (0);
}
