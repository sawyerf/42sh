/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:49:02 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/25 18:35:55 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	reprint(t_rdl *rdl, int curs)
{
	(void)curs;
	left(rdl, rdl->real + rdl->lpro);
	tgpstr("cr");
	tgpstr("cd");
	ft_printf("%s%s", rdl->prompt, rdl->str);
	rdl->real = rdl->size;
	lastcol(rdl);
	left(rdl, rdl->real - curs);
}

int		gtbegin(t_rdl *rdl)
{
	left(rdl, rdl->real % rdl->col);
	return (0);
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

int		is_special(char *buf)
{
	int		count;

	count = 0;
	while (buf[count])
	{
		if (!ft_isprint(buf[count]) && buf[count] != '\n')
			return (1);
		count++;
	}
	return (0);
}
