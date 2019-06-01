#include "jobctl.h"

/*check if sdtin/out are on terminal before init jobctl
  get pgid and fg_p inside loop because our pgid could be changed by parent shell
  
*/

 

int		sh_pause()
{
	if (kill(0, SIGTTIN) == -1)
		return (-1); // maybe retry ?
	return (0);
}

void	dummy_handle(int signum)
{
	(void)signum;
	ft_printf("SEGV recieved\n");
	return ;
}

int		ignore_sigs()
{
	struct sigaction new_act;

	ft_bzero(&new_act, sizeof(struct sigaction));
	new_act.sa_handler = SIG_IGN;
	if ((sigaction(SIGQUIT, &new_act, NULL) < 0)
		|| (sigaction(SIGTSTP,&new_act, NULL) < 0)
		|| (sigaction(SIGTTIN,&new_act, NULL) < 0)
		|| (sigaction(SIGTTOU,&new_act, NULL) < 0)
	/*	|| (sigaction(SIGCHLD,&new_act, NULL) < 0)*/)
		return(SH_ABORT);
	ft_printf("sig_ign set\n");
	return (0);

}


int		reset_sig(void)
{
	struct sigaction new_act;

	ft_bzero(&new_act, sizeof(struct sigaction));
	new_act.sa_handler = SIG_DFL;
	if ((sigaction(SIGQUIT, &new_act, NULL) < 0)
		|| (sigaction(SIGTSTP,&new_act, NULL) < 0)
		|| (sigaction(SIGTTIN,&new_act, NULL) < 0)
		|| (sigaction(SIGTTOU,&new_act, NULL) < 0)
		|| (sigaction(SIGTERM,&new_act, NULL) < 0)
		|| (sigaction(SIGCHLD,&new_act, NULL) < 0))
		return(SH_ABORT);
	return (0);
}
int		enable_jobctl(void)
{
	int pgid;

//	ft_printf("before pgid is: %d\n", getpgrp());
	if (setpgid(0,0) == -1)
		return (SH_ABORT);
	if ((pgid = getpgrp()) == -1)
		return (SH_ABORT);
	if (tcsetpgrp(STDIN_FILENO, pgid) == -1)
		return (SH_ABORT);
	tcgetattr(STDIN_FILENO, &g_sh.term_save);
	ignore_sigs();
/*	if ((pgid = getpgrp()) == -1)
		return (SH_ABORT);
	ft_printf("pgid is : %d\npid is: %d", pgid, getpid());*/
	return (0);
}

int		init_jobctl()
{
	pid_t	pgid;
	pid_t	fg_p;

	ft_printf("initjobctl\n");
	while (42)
	{
		if ((pgid = getpgrp()) == -1)
			return (SH_ABORT);
	//ft_printf("after getpgrp\n");
		if ((fg_p = tcgetpgrp(STDIN_FILENO)) == -1)
			return(SH_ABORT); // stdin not controlling terminal
//	ft_printf("after tcgetpgrp\n");
		if (pgid != fg_p)
		{
			if (sh_pause() == -1)
				return (SH_ABORT);
		}
		else
			return (enable_jobctl());
	}
}
