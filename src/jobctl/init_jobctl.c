/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_jobctl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 18:47:50 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 17:04:17 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobctl.h"

int		sh_pause(void)
{
	if (kill(0, SIGTTIN) == -1)
		return (-1);
	return (0);
}

void	dummy_handle(int signum)
{
	(void)signum;
	ft_printf("SEGV recieved\n");
	return ;
}

int		ignore_sigs(void)
{
	struct sigaction new_act;

	ft_bzero(&new_act, sizeof(struct sigaction));
	new_act.sa_handler = SIG_IGN;
	if ((sigaction(SIGQUIT, &new_act, NULL) < 0)
		|| (sigaction(SIGTSTP, &new_act, NULL) < 0)
		|| (sigaction(SIGTTIN, &new_act, NULL) < 0)
		|| (sigaction(SIGTTOU, &new_act, NULL) < 0))
		return (SH_ABORT);
	ft_printf("sig_ign set\n");
	return (0);
}

int		enable_jobctl(void)
{
	int pgid;

	if (setpgid(0, 0) == -1)
		return (SH_ABORT);
	if ((pgid = getpgrp()) == -1)
		return (SH_ABORT);
	if (tcsetpgrp(STDIN_FILENO, pgid) == -1)
		return (SH_ABORT);
	tcgetattr(STDIN_FILENO, &g_sh.term_save);
	ignore_sigs();
	return (0);
}

int		init_jobctl(void)
{
	pid_t	pgid;
	pid_t	fg_p;

	ft_printf("initjobctl\n");
	while (42)
	{
		if ((pgid = getpgrp()) == -1)
			return (SH_ABORT);
		if ((fg_p = tcgetpgrp(STDIN_FILENO)) == -1)
			return (SH_ABORT);
		if (pgid != fg_p)
		{
			if (sh_pause() == -1)
				return (SH_ABORT);
		}
		else
			return (enable_jobctl());
	}
}
