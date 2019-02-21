/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:49:02 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/21 18:00:25 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"


void	reprint(t_rdl *rdl, int curs)
{
	int adv;

	left(rdl, rdl->curs + rdl->lpro);
	tgpstr("dl");
	adv = ft_printf("%s%s", rdl->prompt, rdl->str);
	left(rdl, adv - rdl->lpro - curs);
}

int		up(t_rdl *rdl, int i)
{
	int count;

	count = 0;
	while (count < i)
	{
		left(rdl, rdl->col);
		count++;
	}
	return (rdl->col * - i);
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

int		left(t_rdl *rdl, int i)
{
	int		count;

	count = 0;
	(void)rdl;
	while (count < i)
	{
		write(1, K_LEFT, 3);
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
		if (!((rdl->lpro + rdl->curs + count + 1) % (rdl->col)))
			tgpstr("do");
		else
			write(1, K_RGHT, 3);
		count++;
	}
	return (i);
}

int		vleft(t_rdl *rdl, int i)
{
	int		count;

	count = 0;
	while (count < i && rdl->curs - count > 0)
	{
		write(1, K_LEFT, 3);
		count++;
	}
	return (-1 * i);
}

int		vright(t_rdl *rdl, int i)
{
	int	count;

	count = 0;
	while (count < i && rdl->size > rdl->curs + count)
	{
		if (!((rdl->lpro + rdl->curs + count + 1) % (rdl->col)))
			tgpstr("do");
		else
			write(1, K_RGHT, 3);
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
		if (!ft_isprint(buf[count]))
			return (1);
		count++;
	}
	return (0);
}
