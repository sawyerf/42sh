/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 20:20:45 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/14 16:07:37 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"
#include "hashtable.h"
#include "builtins.h"

int		br_print(int err, t_cmd_tab *cmd)
{
	(err == br_PATHNOTSET) ? ft_dprintf(2, "PATH not set\n") : 0;
	if (cmd->full_path)
	{
		if (err == br_NOTFOUND)
			ft_dprintf(2, "21sh: %s: command not found\n", cmd->av[0]);
		else if (err == br_PERMDENIED)
			ft_dprintf(2, "21sh: %s: Permission denied\n", cmd->full_path);
		else if (err == br_ISDIR)
			ft_dprintf(2, "21sh: %s: is a directory\n", cmd->full_path);
	}
	else
	{
		if (err == br_NOTFOUND)
			ft_dprintf(2, "21sh: %s: command not found\n", cmd->av[0]);
		else if (err == br_PERMDENIED)
			ft_dprintf(2, "21sh: %s: Permission denied\n", cmd->av[0]);
		else if (err == br_ISDIR)
			ft_dprintf(2, "21sh: %s: is a directory\n", cmd->av[0]);
	}
	if (err == br_PERMDENIED || err == br_ISDIR)
		return (126);
	else if (err == br_NOTFOUND)
		return (127);
	return (err);
}

void	exit_wrap(int code, t_cmd_tab *cmd)
{
	(void)cmd;
	global_del();
	exit(code);
}
