/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hst_use.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:12:42 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/14 12:13:57 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

extern t_list *g_hst[];

t_list	*gethst(void)
{
	return (g_hst[0]);
}

void	hstdellast(void)
{
	t_list *lst;

	if (!g_hst[0])
		return ;
	lst = g_hst[0]->next;
	if (!lst)
		return ;
	free(g_hst[0]->content);
	free(g_hst[0]);
	lst->prev = NULL;
	g_hst[0] = lst;
}

void	hstadd(char *str)
{
	int		i;
	char	*tmp;

	if (!*str || (g_hst[0] && !ft_strcmp(g_hst[0]->content, str)))
		return ;
	if (g_hst[0] && g_hst[0]->next)
		i = (g_hst[0]->content_size / 10) + 1;
	else
		i = 1;
	if (str[ft_strlen(str) - 1] == '\n')
	{
		if (!(tmp = ft_strndup(str, ft_strlen(str) - 1)))
			return ;
	}
	else if (!(tmp = ft_strdup(str)))
		return ;
	str = tmp;
	ft_lstadd(&g_hst[0], ft_lstnew(str, i * 10));
	ft_strdel(&str);
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
