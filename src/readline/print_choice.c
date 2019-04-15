/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_choice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:23:31 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/15 21:45:25 by apeyret          ###   ########.fr       */
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

void	replacefree(char **s1, char **s2)
{
	char	*tmp;

	if (ft_cisin(*s1, '\n'))
	{
		if (!(tmp = ft_replace(*s1, "\n", "^[")))
			return ;
		ft_strdel(s1);
		*s1 = tmp;
	}
	if (ft_cisin(*s2, '\n'))
	{
		if (!(tmp = ft_replace(*s2, "\n", "^[")))
			return ;
		ft_strdel(s2);
		*s2 = tmp;
	}
}

void	putlst(char *mtc, t_list *lst, t_rdl *rdl)
{
	int		max;
	int		i;

	mtc = after(mtc, '/');
	max = get_maxlst(lst) + ft_strlen(mtc) + 2 + 2;
	ft_printf("\n");
	while (lst)
	{
		i = 0;
		while (lst && i < (rdl->col) / max)
		{
			replacefree(&mtc, (char**)&lst->content);
			ft_printf("[%s%s%-*c", mtc, lst->content, max - ft_strlen(mtc)
				- ft_strlen(lst->content) - 3, ((lst->content_size % 10 == 3)
					? '/' : ' '));
			ft_printf("] ");
			lst = lst->next;
			i++;
		}
		ft_printf("\n");
		(lst) ? lst = lst->next : 0;
	}
	ft_printf("%s%s", rdl->prompt, rdl->str);
	rdl->real = rdl->size;
	left(rdl, rdl->size - rdl->curs);
}
