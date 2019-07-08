/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobctl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 20:25:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 20:25:46 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCTL_H
# define JOBCTL_H

# include "sh_core.h"
# include <termios.h>
# include <signal.h>
# define SH_ABORT -1

typedef struct s_cmd_tab	t_cmd_tab;

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
