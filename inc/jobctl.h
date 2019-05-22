#ifndef JOBCTL_H
# define JOBCTL_H

# include "sh_core.h"
# include <termios.h> 
# include <signal.h>
# define SH_ABORT -1

typedef struct s_cmd_tab t_cmd_tab;

t_job	*make_job(int fg);
int		init_jobctl(void);
int		reset_sig(void);
int		setpgid_wrap(pid_t pid, t_job *job);
int		fg_job(t_job *job, int cont);
int		bg_job(t_job *job, int cont);
void	update_job(t_job *job);
void	register_job(t_job *job);
void	free_job(t_job *j);
#endif
