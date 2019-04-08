/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 20:13:04 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/08 17:09:28 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"

t_list *g_hst[4] = {NULL, NULL, NULL, NULL};

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
	len = (ft_strisdigit(s)) ? ft_atoi(s) : ft_strlen(s);
	if (ft_strisdigit(s))
	{
		if (len <= 0)
			len += tmp->content_size / 10;
		while (tmp)
		{
			if ((int)tmp->content_size / 10 == len)
				return (tmp);
			tmp = tmp->next;
		}
		return (hst_pgetcmp(lst, s));
	}
	while (tmp)
	{
		if (!ft_strncmp(s, tmp->content, len))
			return (tmp);
		tmp = tmp->next;
	}
	return (hst_pgetcmp(lst, s));
}
