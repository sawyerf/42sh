/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:42:22 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/04 15:23:00 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "readline.h"

void	fc_reverse(t_list **beg, t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	*lst = *beg;
	*beg = tmp;
}

int		fc_rangel(t_fc fc, t_list **beg, int *i)
{
	t_list	*lst;

	if (!(lst = gethst())
			|| !(lst = lst->next))
		return (1);
	if (fc.range[0])
	{
		*beg = hst_getcmp(lst, fc.range[0]);
		if (fc.range[1])
			lst = hst_getcmp(lst, fc.range[1]);
	}
	else
	{
		if ((int)lst->content_size / 10 - 10 < 0)
			*beg = hst_getcmp(lst, "1");
		else
			*beg = hst_getcmp(lst, ft_itoa((int)lst->content_size / 10 - 10));
	}
	if (!lst || !*beg)
		return (ft_rperr(1, "fc: history specification out of range\n"));
	if (ft_cisin(fc.opt, 'r'))
		fc_reverse(beg, &lst);
	*i = lst->content_size / 10 - ((*beg)->content_size / 10);
	*i += (*i < 0 ? -1 : 1);
	return (0);
}

int		fc_rangee(t_fc fc, t_list **beg, int *i)
{
	t_list	*lst;

	if (!(lst = gethst()))
		return (0);
	*beg = lst;
	if (fc.range[0])
	{
		*beg = hst_getcmp(lst, fc.range[0]);
		if (fc.range[1])
		{
			if (!(lst = hst_getcmp(lst, fc.range[1])))
				return (ft_rperr(1, "fc:history specification out of range\n"));
			*i = lst->content_size / 10 - (*beg)->content_size / 10;
			*i += (*i < 0 ? -1 : 1);
		}
		if (ft_cisin(fc.opt, 'r'))
			fc_reverse(beg, &lst);
	}
	if (!*beg)
		return (ft_rperr(1, "fc: history specification out of range\n"));
	return (0);
}

int		fc_rangele(t_fc fc, t_list **beg, int *i)
{
	t_list	*lst;

	lst = gethst();
	if (!lst || !lst->next)
		return (1);
	lst = lst->next;
	*beg = lst;
	if (fc.range[0])
	{
		*beg = hst_getcmp(lst, fc.range[0]);
		if (fc.range[1])
		{
			lst = hst_getcmp(lst, fc.range[1]);
			*i = lst->content_size / 10 - (*beg)->content_size / 10;
			*i += (*i < 0 ? -1 : 1);
		}
	}
	return (0);
}
