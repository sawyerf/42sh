/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_rdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:15:46 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/06 22:53:29 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "prompt.h"

int		rdlinit(t_rdl *rdl, char *prpt)
{
	if (!(rdl->str = ft_strnew(129)))
		return (MEMERR);
	rdl->paste = NULL;
	rdl->vcurs = 0;
	rdl->size = 0;
	rdl->curs = 0;
	rdl->real = 0;
	rdl->allo = 128;
	tgpstr("cr");
	tgpstr("cd");
	rdl->col = getcolumn();
	rdl->prompt = prompt(prpt);
	rdl->lpro = ft_printf("%s", rdl->prompt);
	lastcol(rdl);
	return (0);
}

void	rdldel(t_rdl *rdl, int curs)
{
	if (curs > rdl->size || rdl->size < 0 ||
		(curs < rdl->curs && rdl->curs <= 0)
		|| (curs >= rdl->curs && rdl->size == curs))
		return ;
	left(rdl, rdl->real);
	ft_strcpy(rdl->str + curs, rdl->str + curs + 1);
	rdl->size--;
	if (curs < rdl->curs)
	{
		reprint(rdl, rdl->curs - 1);
		rdl->curs--;
	}
	else
		reprint(rdl, rdl->curs);
}

void	rdlreplace(t_rdl *rdl, char *s)
{
	if (!s)
		return ;
	left(rdl, rdl->real + rdl->lpro);
	while (rdl->size)
	{
		rdl->str[rdl->size] = 0;
		rdl->size--;
	}
	rdl->str[0] = 0;
	rdl->curs = 0;
	rdl->real = 0;
	tgpstr("cr");
	tgpstr("cd");
	ft_printf("%s", rdl->prompt);
	rdladdstr(rdl, s);
}
