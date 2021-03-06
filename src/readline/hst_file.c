/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hst_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:10:27 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/25 15:58:18 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

extern t_list *g_hst[];
extern t_sh g_sh;

int		hstread(char **env)
{
	int		fd;
	int		i;
	char	*line;
	char	*path;
	char	*home;

	i = 1;
	if (!(home = envchrr(env, "HOME"))
		|| !(path = ft_zprintf("%s/%s", home, ".42sh_history")))
		return (0);
	envaddstr(&g_sh.env, "PATH_HISTORY", path);
	fd = open(path, O_RDONLY);
	ft_strdel(&path);
	if (fd < 0)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		ft_lstadd(&g_hst[0], ft_lstnew(line, 1 + 10 * i));
		ft_strdel(&line);
		i++;
	}
	close(fd);
	return (1);
}

void	hstwrite(int fd, t_list *lst)
{
	if (!lst || lst->content_size % 10)
		return ;
	hstwrite(fd, lst->next);
	ft_dprintf(fd, "%s\n", lst->content);
}

void	hstaddfile(char **env)
{
	int		fd;
	char	*path;
	char	*home;

	path = NULL;
	if (!(home = envchrr(env, "HOME"))
		|| !(path = ft_zprintf("%s/%s", home, ".42sh_history")))
		return ;
	fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0600);
	ft_strdel(&path);
	if (fd < 0)
		return ;
	hstwrite(fd, g_hst[0]);
	close(fd);
	ft_lstdel(&g_hst[0]);
}
