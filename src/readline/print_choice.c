/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_choice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:23:31 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/08 18:35:36 by apeyret          ###   ########.fr       */
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

void	putlst(char *mtc, t_list *lst, t_rdl *rdl)
{
	int		max;
	int		i;

	max = get_maxlst(lst) + 3;
	ft_printf("\n");
	while (lst)
	{
		i = 0;
		while (lst && i < rdl->col / max)
		{
			ft_printf("[%s%s] ", mtc, lst->content);
			lst = lst->next;
			i++;
		}
		ft_dprintf(1, "\n");
		if (lst)
			lst = lst->next;
	}
	ft_printf("%s%s", rdl->prompt, rdl->str);
	left(rdl, rdl->size - rdl->curs);
}
