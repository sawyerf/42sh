/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:52:51 by tduval            #+#    #+#             */
/*   Updated: 2019/06/17 16:56:23 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		lenbefore(t_rdl *rdl, int real)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	if (real < 0 || real > rdl->size)
		return (1);
	while (i < real && rdl->str[i])
	{
		if (nb == i && (rdl->col - 1) && !((rdl->lpro + i) % (rdl->col - 1)))
			nb = -1;
		else if ((rdl->col - 1) && nb && !(nb % (rdl->col - 1)))
			nb = -1;
		else if (rdl->str[i] == '\n')
			nb = -1;
		nb++;
		i++;
	}
	if (nb == i)
		return (nb + rdl->lpro);
	return (nb);
}

int		lenafter(t_rdl *rdl, int real)
{
	int		i;
	int		nb;
	int		aft;

	i = real;
	nb = lenbefore(rdl, real);
	aft = 0;
	if (real < 0 || rdl->real > rdl->size)
		return (1);
	while (rdl->str[i])
	{
		if ((rdl->col - 1) && nb && !(nb % (rdl->col - 1)))
			return (aft);
		else if (rdl->str[i] == '\n')
			return (aft);
		aft++;
		nb++;
		i++;
	}
	return (aft);
}

int		up(t_rdl *rdl, int i)
{
	int len;
	int len2;

	while (i)
	{
		len = lenbefore(rdl, rdl->real);
		if (rdl->real - len < 0)
			return (0);
		left(rdl, len);
		len2 = lenbefore(rdl, rdl->real - 1) + 1;
		if (len2 - len > 0 && rdl->real - (len2 - len) >= 0)
			left(rdl, len2 - len);
		else if (len2 <= len)
			left(rdl, 1);
		else if (rdl->real > 0)
			left(rdl, rdl->real);
		i--;
	}
	return (0);
}

int		down(t_rdl *rdl, int i)
{
	int len;
	int len2;
	int	adv;

	while (i)
	{
		len = lenbefore(rdl, rdl->real) + 1;
		adv = lenafter(rdl, rdl->real);
		right(rdl, adv);
		len2 = lenafter(rdl, rdl->real + 1);
		if (len2 < len && len2)
			right(rdl, len2);
		else if (len && len2)
			right(rdl, len);
		else if (rdl->real + 1 <= rdl->size)
			right(rdl, 1);
		i--;
	}
	return (0);
}
