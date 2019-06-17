/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:17:25 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/17 17:02:22 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	lastcol(t_rdl *rdl)
{
	int len;

	if (rdl->real - 1 >= 0
			&& rdl->real - 1 < rdl->size
			&& rdl->str[rdl->real - 1] == '\n')
		return ;
	len = lenbefore(rdl, rdl->real);
	if (rdl->col && !(len % (rdl->col)))
		tgpstr("do");
}

int		retcc(int cc, t_rdl *rdl, int i, int *count)
{
	tgpstr("up");
	cc = lenbefore(rdl, rdl->real - 1);
	if (cc < i - *count)
	{
		*count += cc;
		rdl->real -= cc;
		cc = 0;
	}
	while (cc > 0)
	{
		write(1, K_RGHT, 3);
		cc--;
	}
	return (cc);
}

int		left(t_rdl *rdl, int i)
{
	int		count;
	int		cc;

	count = -1;
	while (++count < i)
	{
		if ((rdl->real - 1 >= 0 && rdl->size > rdl->real - 1
				&& rdl->str[rdl->real - 1] == '\n')
				|| (rdl->col && !lenbefore(rdl, rdl->real)))
			cc = retcc(cc, rdl, i, &count);
		else if ((cc = lenbefore(rdl, rdl->real)) && cc <= i - count)
		{
			tgpstr("cr");
			count += cc - 1;
			rdl->real -= (cc - 1);
		}
		else
			write(1, K_LEFT, 3);
		rdl->real--;
	}
	return (-i);
}

int		right(t_rdl *rdl, int i)
{
	int	count;
	int cc;
	int lol;

	lol = 0;
	count = 0;
	while (count < i)
	{
		if ((rdl->real >= 0 && rdl->real < rdl->size
				&& rdl->str[rdl->real] == '\n')
				|| (rdl->col && !lenbefore(rdl, rdl->real + 1)))
			tgpstr("do");
		else if ((cc = lenafter(rdl, rdl->real) + 1) && cc <= i - count)
		{
			count += (cc - 1);
			rdl->real += (cc - 1);
			tgpstr("do");
		}
		else
			write(1, K_RGHT, 3);
		rdl->real++;
		count++;
		lol++;
	}
	return (i);
}
