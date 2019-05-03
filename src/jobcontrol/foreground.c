#include "jobctl.h"

void	register_job(t_job *job)
{
	t_job *iter;

	if (!g_sh.job_lst)
		g_sh.job_lst = job;
	else
	{
		iter = g_sh.job_lst;
		while (iter)
		{
			if (iter == job)
				return;
			iter = iter->next;
		}
		iter = g_sh.job_lst;
		while (iter->next)
			iter = iter->next;
		iter->next = job;	
	}
}

void	update_job(t_job *job)
{
	if (!job->pgid)
		job->pgid = WAIT_ANY;
	waitpid(job->pgid, &(job->status), WNOHANG);
}

void	wait_job(t_job *job)
{
	pid_t pid;

	if (!job->pgid)
		job->pgid = WAIT_ANY;
	pid = waitpid(job->pgid, &(job->status), WUNTRACED);
	ft_printf("waitpid ret %d\n", pid);
	if (WIFEXITED(job->status))
	{
		ft_printf("job %d exited normally\n", job->pgid);
	}
	else
	{
		ft_printf("job %d signaled\n", job->pgid);
	}
	register_job(job);
	return;
}


int		fg_job(t_job *job, int cont)
{
	tcsetpgrp(STDIN_FILENO, job->pgid);
	if (cont)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &(job->save_tio));
		if (kill(job->pgid, SIGCONT) < 0)
			ft_dprintf(STDERR_FILENO, "42sh: Error sending cont to pgid %d", job->pgid);
	}
	wait_job(job);
	tcgetattr(STDIN_FILENO, &(job->save_tio)); // save job terminal modes
	tcsetpgrp(STDIN_FILENO, getpgrp());
	return (0);
}

int bg_job(t_job *job, int cont)
{
	if (cont)
	{
		if (kill(job->pgid, SIGCONT) < 0)
			ft_dprintf(STDERR_FILENO, "42sh: Error sending cont to pgid %d", job->pgid);

	}
	register_job(job);
	return (0);
}
