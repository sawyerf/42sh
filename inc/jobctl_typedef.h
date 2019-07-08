/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobctl_typedef.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 20:24:41 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 20:25:07 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int					builtin_exit;
	struct termios		save_tio;
	struct s_job		*next;
	struct s_job		*prev;
}						t_job;

#endif
