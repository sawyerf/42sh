/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 20:20:45 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/09 21:16:30 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"
#include "hashtable.h"
#include "builtins.h"

t_bool	check_fd(int fd)
{
	struct stat	buf;

	if (!fstat(fd, &buf))
		return (FT_TRUE);
	ft_dprintf(STDERR_FILENO, "21sh: bad file descriptor: %d\n", fd);
	return (FT_FALSE);
}

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

void	restore_fd(t_list *to_close)
{
	while (to_close)
	{
		close(*((int*)(to_close->content)));
		to_close = to_close->next;
	}
	dup2(FDSAVEIN, STDIN_FILENO);
	dup2(FDSAVEOUT, STDOUT_FILENO);
	dup2(FDSAVEERR, STDERR_FILENO);
}

void	close_save(void)
{
	close(FDSAVEIN);
	close(FDSAVEOUT);
	close(FDSAVEERR);
}

void	exit_wrap(int code, t_cmd_tab *cmd)
{
	(void)cmd;
	exit(code);
}
