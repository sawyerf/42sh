
#ifndef JOBCTL_TYPEDEF_H
# define JOBCTL_TYPEDEF_H

# include <termios.h>

typedef struct			s_job
{
	char				*cmd_ln;
	pid_t				pgid;
	int					fg;
	int					notified;
	int					status;
	struct termios		save_tio;
	struct s_cmd_tab	*pipeline;
	struct s_job		*next;
}						t_job;

#endif
