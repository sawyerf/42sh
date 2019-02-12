/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_choice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:23:31 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/12 22:42:52 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		get_maxlst(t_list *lst)
{
	int max;
	
	max = 0;
	while (lst)
	{
		if (max < (int)ft_strlen(lst->content))
			max = ft_strlen(lst->content);
		lst = lst->next;
	}
	return (max);
}

char	*after(char *s, int i)
{
	char	*tmp;

	if (!(tmp = ft_strechr(s, i)))
		return (NULL);
	if (*tmp == '/')
		tmp++;
	return (tmp);
}

void	putlst(char *mtc, t_list *lst, t_rdl *rdl)
{
	int		max;
	int		i;

	mtc = after(mtc, '/');
	max = get_maxlst(lst) + ft_strlen(mtc) + 2 + 1;
	ft_printf("\n");
	while (lst)
	{
		i = 0;
		while (lst && i < (rdl->col) / max)
		{
			ft_printf("[%s%-*s", mtc, max - ft_strlen(mtc) - 3, lst->content);
			if (lst->content_size == 3)
				ft_printf("/");
			ft_printf("] ");
			lst = lst->next;
			i++;
		}
		ft_printf("\n");
		if (lst)
			lst = lst->next;
	}
	ft_printf("%s%s", rdl->prompt, rdl->str);
	left(rdl, rdl->size - rdl->curs);
}
