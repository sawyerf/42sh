/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 20:13:04 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/19 18:43:44 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_list *g_hst[3] = {NULL, NULL};

void	hstadd(char *str)
{
	if (g_hst[0] && !ft_strcmp(g_hst[0]->content, str))
		return ;
	ft_lstadd(&g_hst[0], ft_lstnew(str, 0));
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
}
