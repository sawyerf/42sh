/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:24:20 by ktlili            #+#    #+#             */
/*   Updated: 2019/05/28 17:26:04 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

 int	refresh_jobs(void)
{
	t_job *j;
	pid_t chld;

	j = g_sh.job_lst;
	while (j)
	{
		chld = waitpid(-(j->pgid), &(j->status), WUNTRACED | WNOHANG | WCONTINUED);
		if (WIFSIGNALED(j->status))
		{
//			ft_printf("x[%d] '%s' recieved signal %d\n", j->pgid, j->cmd_ln, WTERMSIG(j->status));
			j->completed = 1;
		}
		if ((chld > 0) && (WIFEXITED(j->status))) /* waitpid return 0 if child hasent changed state*/
			j->completed = 1;
		if (WIFSTOPPED(j->status))
			j->stopped = 1;
		else
			j->stopped = 0;
		j = j->next;		
	}
	ft_printf("--------------------\n");
	return (0);
}
/* no malloc, null ret for inexistant job
*/

int		invalid_opt(void)
{
	ft_dprintf(STDERR_FILENO, "42sh: jobs: invalid option");
	ft_dprintf(STDERR_FILENO, "jobs : usage : jobs [-ln] [jobspec]\n" );
	return (0);
}


void	jobs_print_l(t_job *j)
{
	char curr;

	curr = 0;
	if (j == g_sh.current_j)
		curr = '+';
	else if (j == g_sh.previous_j)
		curr = '-';
	ft_printf("[%d]%c %d '%s' ", j->job_id, curr, j->pgid, j->cmd_ln);
	if (j->completed)
	{
		j->notified = 1;
		ft_printf("completed %.d\n", (int)WEXITSTATUS(j->status));
	}
	else if (j->stopped)
		ft_printf("stopped\n");
	else
		ft_printf("running\n");
	
}

int		jobs_print_all(t_job_print jobs_printer)
{
	t_job *j;

	j = g_sh.job_lst;
	while (j)
	{
		jobs_printer(j);
		j = j->next;
	}
	return (0); // will change
}

int		jobs(t_cmd_tab *cmd)
{
	t_job *arg_job;
	t_job_print	jobs_printer;
	char opt;
	int	i;

	opt = 'l';
	g_optind = 1;
	while ((i = ft_getopt(cmd->av, "lp")) != -1)
	{
		opt = (char)i;
		if (opt == '?')
			return (invalid_opt());
	}
	refresh_jobs();
	jobs_printer = jobs_print_l;
	i = g_optind ; // temp hack
	if (!(cmd->av[i]))
		return (jobs_print_all(jobs_printer));
	while (cmd->av[i])
	{
		if (!(arg_job = jobs_conversion(cmd->av[i])))
			ft_dprintf(STDERR_FILENO, "42sh: jobs: '%s': no such job\n", cmd->av[i]);
		else
		{
			jobs_printer(arg_job);
			arg_job->notified = 1;
		}
		i++;
	}
	return (0); //nope
}
