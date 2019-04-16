#ifndef JOBCTL_H
# define JOBCTL_H

#include "sh_core.h"
# include <termios.h> 
# define SH_ABORT -1




t_job	*make_job(struct s_cmd_tab *pipeline);
int	init_jobctl(void);
int	reset_sig(void);
int	setpgid_wrap(pid_t pid, t_job *job);
#endif
