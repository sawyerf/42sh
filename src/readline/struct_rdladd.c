/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_rdladd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:19:37 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/24 21:07:26 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		lenisprint(char *buf)
{
	int		i;

	i = 0;
	while (*buf)
	{
		if (ft_isprint(*buf) || *buf == '\n')
			i++;
		buf++;
	}
	return (i);
}

int		rdl_realloc(t_rdl *rdl)
{
	char	*tmp;

	tmp = rdl->str;
	if (!(rdl->str = ft_strnew(rdl->allo + 128)))
	{
		rdl->str = tmp;
		return (MEMERR);
	}
	rdl->allo += 128;
	ft_strcpy(rdl->str, tmp);
	ft_strdel(&tmp);
	return (0);
}

int		rdladdstr(t_rdl *rdl, char *str)
{
	int	count;
	int len;

	if (!str || !(len = lenisprint(str)))
		return (0);
	if (len + rdl->size > rdl->allo)
	{
		rdl->allo = rdl->size + len;
		if (rdl_realloc(rdl))
		{
			rdl->allo -= len;
			return (MEMERR + 1);
		}
	}
	left(rdl, rdl->real + rdl->lpro);
	ft_memmove(rdl->str + rdl->curs + len, rdl->str + rdl->curs,
			rdl->size - rdl->curs);
	count = 0;
	while (str[count])
	{
		if (ft_isprint(str[count]) || str[count] == '\n')
			rdl->str[rdl->curs + count] = str[count];
		count++;
	}
	rdl->size += len;
	rdl->curs += len;
	reprint(rdl, rdl->curs);
	return (0);
}

int		rdladd(t_rdl *rdl, char c)
{
	if (!rdl->str)
		return (0);
	if (rdl->allo == rdl->size)
	{
		if (rdl_realloc(rdl))
			return (MEMERR + 1);
	}
	left(rdl, rdl->real + rdl->lpro);
	ft_memmove(rdl->str + rdl->curs + 1, rdl->str + rdl->curs,
			rdl->size - rdl->curs);
	rdl->str[rdl->curs] = c;
	rdl->size++;
	rdl->curs++;
	reprint(rdl, rdl->curs);
	return (0);
}
