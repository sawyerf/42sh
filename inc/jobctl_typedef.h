
#ifndef JOBCTL_TYPEDEF_H
# define JOBCTL_TYPEDEF_H

# include <termios.h>

typedef struct			s_job
{
	pid_t				pgid;
	int					notified;
	struct termios		save_tio;
	int					status;
	struct s_cmd_tab	*pipeline;
	struct s_job		*next;

}						t_job;

#endif
