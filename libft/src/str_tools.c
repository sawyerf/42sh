/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:15:46 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/03 21:13:39 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

int		str_init(t_stri *rdl)
{
	if (!(rdl->str = ft_strnew(129)))
		return (MEMERR);
	rdl->size = 0;
	rdl->curs = 0;
	rdl->allo = 128;
	return (0);
}

int		str_del(t_stri *rdl, int curs)
{
	if (curs > rdl->size || rdl->size < 0
		|| (curs < rdl->curs && rdl->curs <= 0)
		|| (curs >= rdl->curs && rdl->size == curs))
		return (0);
	ft_strcpy(rdl->str + curs, rdl->str + curs + 1);
	rdl->size--;
	if (curs < rdl->curs)
		rdl->curs--;
	return (0);
}

int		str_replaceall(t_stri *rdl, char *s)
{
	if (!s)
		return (0);
	while (rdl->size)
	{
		rdl->str[rdl->size] = 0;
		rdl->size--;
	}
	rdl->str[0] = 0;
	rdl->curs = 0;
	if (str_addstr(rdl, s) == MEMERR)
		return (MEMERR);
	return (0);
}
