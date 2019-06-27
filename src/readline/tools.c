/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:49:02 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/27 19:16:38 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

extern t_list *g_hst[];

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

void	ctrlr_del(t_rdl *hst)
{
	ft_strdel(&hst->str);
	ft_strdel(&hst->prompt);
	ft_strdel(&hst->paste);
	g_hst[3] = NULL;
}
