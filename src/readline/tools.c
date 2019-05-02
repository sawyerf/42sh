/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:49:02 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/01 18:18:17 by apeyret          ###   ########.fr       */
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
