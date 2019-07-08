/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_sig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 16:29:26 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 19:35:11 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobctl.h"

int		reset_sig(void)
{
	struct sigaction new_act;

	ft_bzero(&new_act, sizeof(struct sigaction));
	new_act.sa_handler = SIG_DFL;
	new_act.sa_flags = SA_RESTART;
	if ((sigaction(SIGQUIT, &new_act, NULL) < 0)
		|| (sigaction(SIGTSTP, &new_act, NULL) < 0)
		|| (sigaction(SIGTTIN, &new_act, NULL) < 0)
		|| (sigaction(SIGTTOU, &new_act, NULL) < 0)
		|| (sigaction(SIGTERM, &new_act, NULL) < 0)
		|| (sigaction(SIGCHLD, &new_act, NULL) < 0))
		return (SH_ABORT);
	return (0);
}
