/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_stradd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:19:37 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/03 21:13:29 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

int		str_realloc(t_stri *rdl)
{
	char	*tmp;

	tmp = rdl->str;
	if (!(rdl->str = ft_strnew(rdl->allo + 128)))
	{
		ft_strdel(&tmp);
		rdl->size = 0;
		rdl->allo = 0;
		rdl->curs = 0;
		return (MEMERR);
	}
	rdl->allo += 128;
	ft_strcpy(rdl->str, tmp);
	ft_strdel(&tmp);
	return (0);
}

int		str_addstr(t_stri *rdl, char *str)
{
	int	count;
	int len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len + rdl->size > rdl->allo)
	{
		rdl->allo += len;
		if (str_realloc(rdl) == MEMERR)
			return (MEMERR);
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
	rdl->curs += len;
	return (0);
}

int		str_add(t_stri *rdl, char c)
{
	if (!rdl->str)
		rdl->allo = 0;
	if (rdl->allo <= rdl->size)
		if (str_realloc(rdl) == MEMERR)
			return (MEMERR);
	ft_memmove(rdl->str + rdl->curs + 1, rdl->str + rdl->curs,
		rdl->size - rdl->curs);
	rdl->str[rdl->curs] = c;
	rdl->size++;
	rdl->curs++;
	return (0);
}
