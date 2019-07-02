#include "sh_core.h"

t_sig	g_sig[] =\
{
	{SIGHUP, "SIGHUP"},
	{SIGINT, "SIGINT"},
	{SIGQUIT, "SIGQUIT"},
	{SIGILL, "SIGILL"},
	{SIGABRT, "SIGABRT"},
	{SIGFPE, "SIGFPE"},
	{SIGKILL, "SIGKILL"},
	{SIGSEGV, "SIGSEGV"},
	{SIGPIPE, "SIGPIPE"},
	{SIGALRM, "SIGALRM"},
	{SIGTERM, "SIGTERM"},
	{SIGSTOP, "SIGSTOP"},
	{SIGTSTP, "SIGTSTP"},
	{SIGTTIN, "SIGTTIN"},
	{SIGTTOU, "SIGTTOU"},
	{SIGBUS, "SIGBUS"},
	{SIGXCPU, "SIGXCPU"},
	{SIGXFSZ, "SIGXFSZ"},
	{SIGVTALRM, "SIGVTALRM"},
	{SIGPROF, "SIGPROF"},
	{0, NULL},
};

char	*get_termsig(int signum)
{
	int i;

	i = 0;
	while (g_sig[i].sigstr)
	{
		if (signum == g_sig[i].signum)
			return (g_sig[i].sigstr);
		i++;
	}
	return("Unknown termination signal");
}

void	print_sigexit(t_job *job)
{
	int signum;

	signum = WTERMSIG(job->status);
	if (signum == SIGINT)
		return ;
	ft_printf("42h: %d terminated by signal %s\n", job->pgid,
			get_termsig(signum));
}
