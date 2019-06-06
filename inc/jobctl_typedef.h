#ifndef JOBCTL_TYPEDEF_H
# define JOBCTL_TYPEDEF_H

# include <termios.h>

typedef struct			s_job
{
	char				*cmd_ln;
	pid_t				pgid;
	size_t				job_id;
	int					fg;
	int					notified;
	int					completed;
	int					stopped;
	int					status; 
	struct termios		save_tio;
	struct s_job		*next;
	struct s_job		*prev;
}						t_job;

#endif
