/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:17:25 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/07 16:08:14 by apeyret          ###   ########.fr       */
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

int		up(t_rdl *rdl, int i)
{
	int count;

	count = 0;
	while (count < i)
	{
		tgpstr("up");
		rdl->real -= rdl->col;
		count++;
	}
	return (rdl->col * -i);
}

int		down(t_rdl *rdl, int i)
{
	int count;

	count = 0;
	while (count < i)
	{
		right(rdl, rdl->col);
		count++;
	}
	return (rdl->col * i);
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
