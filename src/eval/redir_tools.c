/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 16:01:57 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 16:26:36 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

int		is_fifo(char *path)
{
	struct stat buf;

	if (lstat(path, &buf) != 0)
		return (0);
	if (S_ISFIFO(buf.st_mode))
		return (1);
	return (0);
}

int		redir_fd_range(int fd)
{
	if ((fd >= 0) && (fd < 256))
		return (0);
	ft_dprintf(STDERR_FILENO, "42sh: File descriptor %d is out of range\n", fd);
	return (-1);
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

t_bool	check_fd(int fd)
{
	struct stat	buf;

	if (!fstat(fd, &buf))
		return (FT_TRUE);
	ft_dprintf(STDERR_FILENO, "42sh: bad file descriptor: %d\n", fd);
	return (FT_FALSE);
}
