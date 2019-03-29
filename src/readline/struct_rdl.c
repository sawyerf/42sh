/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_rdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:15:46 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/29 18:32:24 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		rdlinit(t_rdl *rdl, char *prompt)
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
	rdl->lpro = ft_printf("%s", prompt);
	lastcol(rdl);
	rdl->prompt = prompt;
	return (0);
}

void	rdldel(t_rdl *rdl, int curs)
{
	if (curs > rdl->size || rdl->size < 0 ||
		(curs < rdl->curs && rdl->curs <= 0)
		|| (curs >= rdl->curs && rdl->size == curs))
		return ;
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

void	rdl_realloc(t_rdl *rdl)
{
	char	*tmp;

	tmp = rdl->str;
	if (!(rdl->str = ft_strnew(rdl->allo + 128)))
		return ;
	rdl->allo += 128;
	ft_strcpy(rdl->str, tmp);
	ft_strdel(&tmp);
}

void	rdladdstr(t_rdl *rdl, char *str)
{
	int	count;
	int len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len + rdl->size > rdl->allo)
	{
		rdl->allo = rdl->size + len;
		rdl_realloc(rdl);
	}
	ft_memmove(rdl->str + rdl->curs + len, rdl->str + rdl->curs,
		rdl->size - rdl->curs);
	count = 0;
	while (str[count])
	{
		rdl->str[rdl->curs + count] = str[count];
		count++;
	}
	rdl->size += len;
	ft_printf("%s", rdl->str + rdl->curs);
	rdl->real = rdl->size;
	lastcol(rdl);
	rdl->curs += len;
	left(rdl, rdl->real - rdl->curs);
}

void	rdladd(t_rdl *rdl, char c)
{
	int adv;

	if (!rdl->str)
		return ;
	if (rdl->allo == rdl->size)
		rdl_realloc(rdl);
	ft_memmove(rdl->str + rdl->curs + 1, rdl->str + rdl->curs,
		rdl->size - rdl->curs);
	rdl->str[rdl->curs] = c;
	rdl->size++;
	adv = ft_printf("%s", rdl->str + rdl->curs);
	rdl->real += adv;
	lastcol(rdl);
	rdl->curs++;
	left(rdl, rdl->real - rdl->curs);
}
