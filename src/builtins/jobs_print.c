/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:16:06 by tduval            #+#    #+#             */
/*   Updated: 2019/06/26 13:42:07 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	jobs_print_p(t_job *j)
{
	ft_printf("%d\n", j->pgid);
}

void	jobs_print_l(t_job *j)
{
	char curr;

	curr = 0;
	if (j == g_sh.current_j)
		curr = '+';
	else if (j == g_sh.previous_j)
		curr = '-';
	ft_printf("[%d]%c %d '%s' ", j->job_id, curr, j->pgid, j->cmd_ln);
	if (j->completed)
	{
		j->notified = 1;
		ft_printf("completed %.d\n", (int)WEXITSTATUS(j->status));
	}
	else if (j->stopped)
		ft_printf("stopped\n");
	else
		ft_printf("running\n");
}

int		jobs_print_all(t_job_print jobs_printer)
{
	t_job *j;

	j = g_sh.job_lst;
	while (j)
	{
		jobs_printer(j);
		j = j->next;
	}
	return (0);
}
