#include "jobctl.h"

int		setpgid_wrap(pid_t pid, t_job *job)
{
	if (!pid)
		pid = getpid();
	if (!job->pgid)
		job->pgid = pid;
	if (setpgid(pid, job->pgid) == -1)
		return (-1);
	return (0);	

}

int		fg_job(t_job *job, int cont)
{
	if (cont)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &(job->save_tio));
		if (kill(job->pgid, SIGCONT) < 0)
			ft_dprintf(STDERR_FILENO, "42sh: Error sending cont to pgid %d", job->pgid);
	}
	tcsetpgrp(STDIN_FILENO, job->pgid);
	wait_wrapper(job->pipeline, job->pgid); // should continue if job suspended
	tcgetattr(STDIN_FILENO, &(job->save_tio)); // save job terminal modes
	tcsetpgrp(STDIN_FILENO, getpgrp());
	return (0);
}

t_job	*make_job(t_cmd_tab *pipeline)
{
	t_job	*job;
	
	if (!(job = ft_memalloc(sizeof(t_job))))
		return (NULL);
	ft_bzero(job, sizeof(t_job));
	job->pipeline = pipeline;
	job->fg = 1;
//	if (!(job->cmd_ln = make_cmdln(pipeline)))
//		return (NULL);
	return (job);
}
