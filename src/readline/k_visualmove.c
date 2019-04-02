/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_visualmove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:06:38 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/01 18:08:11 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		vm_left(t_rdl *rdl)
{
	if (rdl->vcurs >= rdl->curs)
		ft_printf("\e[7m%c\e[0m", rdl->str[rdl->curs]);
	else
		ft_printf("\e[0m%c", rdl->str[rdl->curs]);
	rdl->real++;
	lastcol(rdl);
	rdl->curs++;
	left(rdl, 2);
	rdl->curs -= 2;
	return (0);
}

int		vm_right(t_rdl *rdl)
{
	if (rdl->vcurs <= rdl->curs)
		ft_printf("\e[7m%c\e[0m", rdl->str[rdl->curs]);
	else
		ft_printf("\e[0m%c", rdl->str[rdl->curs]);
	rdl->real++;
	lastcol(rdl);
	rdl->curs++;
	left(rdl, 1);
	rdl->curs--;
	right(rdl, 1);
	rdl->curs++;
	return (0);
}

int		vm_move(t_rdl *rdl, char *buf)
{
	if (!ft_strcmp(K_LEFT, buf) && rdl->curs > 0 && rdl->curs != rdl->size)
		vm_left(rdl);
	else if (!ft_strcmp(K_RGHT, buf) && rdl->size > rdl->curs)
		vm_right(rdl);
	else if (!ft_strcmp(K_LEFT, buf) && rdl->curs > 0 && rdl->curs == rdl->size)
	{
		left(rdl, 1);
		rdl->curs--;
	}
	return (0);
}
