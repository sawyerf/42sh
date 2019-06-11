/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:17:25 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/08 16:31:19 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

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
	if (rdl->col && !((rdl->lpro + rdl->real) % (rdl->col)))
		tgpstr("do");
}

int		left(t_rdl *rdl, int i)
{
	int		count;
	int		cc;

	count = 0;
	while (count < i)
	{
		if (rdl->col && !((rdl->lpro + rdl->real) % (rdl->col)))
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
		if (rdl->col && !((rdl->lpro + rdl->real + 1) % (rdl->col)))
			tgpstr("do");
		else
			write(1, K_RGHT, 3);
		rdl->real++;
		count++;
	}
	return (i);
}
