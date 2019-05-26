/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:24:20 by ktlili            #+#    #+#             */
/*   Updated: 2019/05/03 16:36:41 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

 int	refresh_jobs(void)
{
	t_job *j;
	pid_t chld;
	ft_printf("---refreshing jobs---\n");
	j = g_sh.job_lst;
	while (j)
	{
		chld = waitpid(-(j->pgid), &(j->status), WUNTRACED | WNOHANG | WCONTINUED);
		if (WIFSIGNALED(j->status))
		{
			ft_printf("[%d] '%s' recieved signal %d\n", j->pgid, j->cmd_ln, WTERMSIG(j->status));
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
t_job	*jobs_conversion(char *arg)
{
	if ((!arg) || (*arg != '%') || !(*(arg + 1)))
		return (NULL);
	if (*(arg + 1) == '%')
		return (jobs_conv_pct(arg + 1));
	else if (*(arg + 1) == '+')
		return (jobs_conv_min(arg + 1));
	else if (*(arg + 1) == '-')
		return (jobs_conv_min(arg + 1));
	else if (ft_isalldigit(arg + 1))
		return (jobs_conv_num(arg + 1));
	else if (*(arg + 1) == '?')
		return (jobs_conv_cmd(arg + 1));
	else
		return (jobs_conv_any(arg + 1));
	
}

int		invalid_opt(void)
{
	ft_dprintf(STDERR_FILENO, "42sh: jobs: invalid option");
	ft_dprintf(STDERR_FILENO, "jobs : usage : jobs [-ln] [jobspec]\n" );
	return (0);
}


void	jobs_print_l(t_job *j)
{

	ft_printf("[%d] %d '%s'", j->job_id, j->pgid, j->cmd_ln);
	if (j->completed)
		ft_printf("completed %.d\n", (int)WEXITSTATUS(j->status));
	else if (j->stopped)
		ft_printf(" stopped\n");
	else
		ft_printf(" running\n");
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
			ft_dprintf(STDERR_FILENO, "42sh: jobs: '%s': nah bruh\n", cmd->av[i]);
		else
			jobs_printer(arg_job);
		arg_job->notified = 1;
		i++;
	}
	return (0); //nope
}






/*
int		jobs(t_cmd_tab *cmd)
{
	t_job	*j;
	int		i;

	(void)cmd;
	i = 0;
	j = g_sh.job_lst;
	if (refresh_jobs())
		return (-1);
	if (!j)
	{
		ft_dprintf(STDERR_FILENO, "42sh: jobs: No jobs currently running\n");
		return (0);
	}
	while (j)
	{
		ft_printf("[%d] %d '%s'", i, j->pgid, j->cmd_ln);
		if (j->completed)
			ft_printf(" completed\n");
		else if (j->stopped)
			ft_printf(" stopped\n");
		else
			ft_printf(" running\n");
		j->notified = 1;
		j = j->next;
		i++;
	}
	return (0);

}*/
