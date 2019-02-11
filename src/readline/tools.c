/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:49:02 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/11 18:36:49 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	left(t_rdl *rdl, int i)
{
	(void)rdl;
	while (i)
	{
		write(1, K_LEFT, 3);
		i--;
	}
}

void	right(t_rdl *rdl, int i)
{
	int	count;

	count = 0;
	while (count < i)
	{
		if (!((rdl->lpro + rdl->curs + count) % (rdl->col - 1)))
			tgpstr("do");
		else
			write(1, K_RGHT, 3);
		count++;
	}
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
