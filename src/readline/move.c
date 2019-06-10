/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:17:25 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/07 16:51:55 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		lenbefore(t_rdl *rdl, int real)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	if (real < 0)
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
	if (real < 0)
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

void	lastcol(t_rdl *rdl)
{
	int len;

	if (rdl->real - 1>= 0 && rdl->real - 1< rdl->size && rdl->str[rdl->real - 1] == '\n')
		return ;
	len = lenbefore(rdl, rdl->real);
	if (rdl->col && !(len % (rdl->col)))
	{
		//ft_printf("[%d/%d]\n", len, rdl->col);
		tgpstr("do");
	}
}


int		left(t_rdl *rdl, int i)
{
	int		count;
	int		cc;

	count = 0;
	while (count < i)
	{
		if (rdl->real - 1 >= 0 && rdl->size > rdl->real - 1 && rdl->str[rdl->real - 1] == '\n')
		{
			tgpstr("up");
			cc = lenbefore(rdl, rdl->real - 1);
			while (cc)
			{
				write(1, K_RGHT, 3);
				cc--;
			}
		}
		else if (rdl->col && !(lenbefore(rdl, rdl->real) % (rdl->col)))
		{
			tgpstr("up");
			cc = 0;
			while (rdl->col > cc)
			{
				write(1, K_RGHT, 3);
				cc++;
			}
		}
		else
			write(1, K_LEFT, 3);
		rdl->real--;
		count++;
	}
	return (-1 * i);
}

int		right(t_rdl *rdl, int i)
{
	int	count;

	count = 0;
	while (count < i)
	{
		if (rdl->real >= 0 && rdl->real < rdl->size && rdl->str[rdl->real] == '\n')
			tgpstr("do");
		else if (rdl->col && rdl->real > 0 && !(lenbefore(rdl, rdl->real + 1) % (rdl->col)))
			tgpstr("do");
		else
			write(1, K_RGHT, 3);
		rdl->real++;
		count++;
	}
	return (i);
}
