/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 20:13:04 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/18 20:14:23 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"

t_list *g_hst[4] = {NULL, NULL, NULL, NULL};

t_list	*gethst(void)
{
	return (g_hst[0]);
}

void	hstdellast(void)
{
	t_list *lst;

	lst = g_hst[0]->next;
	free(g_hst[0]->content);
	free(g_hst[0]);
	lst->prev = NULL;
	g_hst[0] = lst;
}

void	hstadd(char *str)
{
	int		i;

	if (g_hst[0] && !ft_strcmp(g_hst[0]->content, str))
		return ;
	if (g_hst[0] && g_hst[0]->next)
		i = (g_hst[0]->content_size / 10) + 1;
	else
		i = 1;
	ft_lstadd(&g_hst[0], ft_lstnew(str, i * 10));
}

int		hstread(char **env)
{
	int		fd;
	int		i;
	char	*line;
	char	*path;
	char	*home;

	i = 1;
	if (!(home = envchrr(env, "HOME"))
		|| !(path = ft_zprintf("%s/%s", home, ".21sh_history")))
		return (0);
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

char	*hstchc(char *s)
{
	g_hst[3] = g_hst[0];
	if (!s || !s[0])
	{
		g_hst[3] = NULL;
		return (NULL);
	}
	while (g_hst[3])
	{
		if (ft_strstr(g_hst[3]->content, s))
			return (g_hst[3]->content);
		g_hst[3] = g_hst[3]->next;
	}
	return (NULL);
}

int		hstnchc(t_rdl *rdl, char *buf)
{
	(void)buf;
	if (g_hst[3])
		g_hst[3] = g_hst[3]->next;
	else
		g_hst[3] = g_hst[0];
	if (!rdl->str || !rdl->str[0])
		return (1);
	while (g_hst[3])
	{
		if (ft_strstr(g_hst[3]->content, rdl->str))
			return (0);
		g_hst[3] = g_hst[3]->next;
	}
	hstchc(rdl->str);
	return (0);
}

char	*hstnext(char *s)
{
	if (!g_hst[1])
	{
		hstreset();
		g_hst[2] = ft_lstnew(s, 0);
		if (!g_hst[0])
			return (NULL);
		g_hst[1] = g_hst[0];
		return (g_hst[0]->content);
	}
	if (g_hst[1]->next)
	{
		g_hst[1] = g_hst[1]->next;
		return (g_hst[1]->content);
	}
	return (NULL);
}

char	*hstprev(void)
{
	if (g_hst[1] && g_hst[1]->prev)
	{
		g_hst[1] = g_hst[1]->prev;
		return (g_hst[1]->content);
	}
	else if (g_hst[2])
	{
		g_hst[1] = NULL;
		return (g_hst[2]->content);
	}
	return (NULL);
}

void	hstreset(void)
{
	g_hst[1] = NULL;
	if (g_hst[2])
	{
		ft_strdel((char**)&g_hst[2]->content);
		free(g_hst[2]);
	}
	g_hst[2] = NULL;
	g_hst[3] = NULL;
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
		|| !(path = ft_zprintf("%s/%s", home, ".21sh_history")))
		return ;
	fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0600);
	ft_strdel(&path);
	if (fd < 0)
		return ;
	hstwrite(fd, g_hst[0]);
	close(fd);
}

t_list	*hst_pgetcmp(t_list *lst, char *s)
{
	t_list	*tmp;
	int		len;

	tmp = lst;
	if (ft_strisdigit(s))
	{
		len = ft_atoi(s);
		if (len < 0)
			len += tmp->content_size / 10;
		while (tmp)
		{
			if ((int)tmp->content_size / 10 == len)
				return (tmp);
			tmp = tmp->prev;
		}
		return (NULL);
	}
	len = ft_strlen(s);
	while (tmp)
	{
		if (!ft_strncmp(s, tmp->content, len))
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}

t_list	*hst_getcmp(t_list *lst, char *s)
{
	t_list	*tmp;
	int		len;

	tmp = lst;
	if (ft_strisdigit(s))
	{
		len = ft_atoi(s);
		if (len <= 0)
			len += tmp->content_size / 10;
		while (tmp)
		{
			if ((int)tmp->content_size / 10 == len)
				return (tmp);
			tmp = tmp->next;
		}
	}
	else
	{
		len = ft_strlen(s);
		while (tmp)
		{
			if (!ft_strncmp(s, tmp->content, len))
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (hst_pgetcmp(lst, s));
}
