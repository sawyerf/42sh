#include "builtins.h"



static int	refresh_jobs(void)
{
	t_job *j;

	j = g_sh.job_lst;
	while (j)
	{
		waitpid(j->pgid, &(j->status), WUNTRACED|WNOHANG);
		if (WIFSIGNALED(j->status))
		{
			ft_printf("[%d] '%s' recieved signal %d\n", j->pgid, j->cmd_ln, WTERMSIG(j->status));
		}
		if (WIFEXITED(j->status))
			j->completed = 1;
		if (WIFSTOPPED(j->status))
			j->stopped = 1;
		j = j->next;		
	}
	return (0);
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
		if (j->stopped)
			ft_printf(" stopped\n");
		j = j->next;
		i++;
	}
	return (0);

}
