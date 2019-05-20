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

static int	refresh_jobs(void)
{
	t_job *j;
	pid_t chld;

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
	return (0);
}
# define INVALIDCONV -1

t_job	*jobs_conversion(char *arg)
{
	if ((!arg) || (*arg != '%') || !(*(arg + 1)))
		return (INVALIDCONV);
	if (*(arg + 1) == '%')
		return (conv_percent(arg + 1));
	else if (*(arg + 1) == '+')
		return (conv_percent(arg + 1));
	else if (ft_isalldigit(arg + 1))
		return (conv_num(arg + 1));
	else if (*(arg + 1) == '?')
		return (conv_strstr(arg + 1));
	else
		return (conv_strcmp(arg + 1));
	
}

int		invalid_opt(void)
{
	ft_dprintf(STDERR_FILENO, "42sh: jobs: invalid option");
	ft_dprintf(STDERR_FILENO, "jobs : usage : jobs [-ln] [jobspec]\n" );
	return (0);
}




int		jobs(t_cmd_tab *cmd)
{
	t_job 
	char opt;
	int	ret;

	opt = 'l';
	g_optind = 1;
	while ((ret = ft_getopt(cmd->av, "lp")) != -1)
	{
		opt = (char)ret;
		if (opt == '?')
			return (invalid_opt());
	}

}







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

}
