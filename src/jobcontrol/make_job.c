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

t_job	*make_job(int fg)
{
	t_job	*job;
	
	if (!(job = ft_memalloc(sizeof(t_job))))
		return (NULL);
	ft_bzero(job, sizeof(t_job));
	if (fg)
		job->fg = 1;

//	if (!(job->cmd_ln = make_cmdln(pipeline)))
//		return (NULL);
	return (job);
}
