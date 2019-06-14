/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:49:02 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/14 13:33:35 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	reprint(t_rdl *rdl, int curs)
{
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

int		is_special(char *buf)
{
	while (*buf)
	{
		if (ft_cisin(SPECIAL, *buf))
			return (1);
		buf++;
	}
	return (0);
}
