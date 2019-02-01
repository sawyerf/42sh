/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_rdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:15:46 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/01 17:44:36 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	rdlinit(t_rdl *rdl)
{
	if (!(rdl->str = ft_strnew(129)))
		return ;
	rdl->size = 0;
	rdl->curs = 0;
	rdl->allo = 128;
}

void	rdldel(t_rdl *rdl, int curs)
{
	//ft_printf("%d/", rdl->curs);
	if (curs > rdl->size || rdl->size < 0 || rdl->curs <= 0)
		return ;
	ft_strcpy(rdl->str + curs, rdl->str + curs + 1);
	rdl->size--;
	rdl->curs--;
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

void	rdladd(t_rdl *rdl, char c)
{
	if (!rdl->str)
		return ;
	if (rdl->allo == rdl->size)
		rdl_realloc(rdl);
	ft_memmove(rdl->str + rdl->curs + 1, rdl->str + rdl->curs, rdl->size - rdl->curs);
	rdl->str[rdl->curs] = c;
	rdl->size++;
	rdl->curs++;
}
