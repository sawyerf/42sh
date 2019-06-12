/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 14:09:24 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/12 18:58:33 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_replace(char *s, char c1, char c2, int len)
{
	int count;

	count = 0;
	while (count < len)
	{
		if (s[count] == c1)
		{
			s[count] = c2;
			return ;
		}
		count++;
	}
}

int		lenall(t_printf *lst)
{
	int nb;

	nb = 0;
	while (lst)
	{
		nb += lst->len;
		lst = lst->next;
	}
	return (nb);
}
