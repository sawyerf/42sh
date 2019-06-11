/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_rdladd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:19:37 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/01 18:19:58 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

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
