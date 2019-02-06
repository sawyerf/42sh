/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_rdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:15:46 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/05 18:57:02 by alarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	rdlinit(t_rdl *rdl, char *PROMPT)
{
	if (!(rdl->str = ft_strnew(129)))
		return ;
	rdl->size = 0;
	rdl->curs = 0;
	rdl->allo = 128;
	rdl->lpro = ft_printf("%s", PROMPT);
	rdl->prompt = PROMPT;
	rdl->col = getcolumn();
}

void	rdldel(t_rdl *rdl, int curs)
{
	int adv;

	if (curs > rdl->size || rdl->size < 0 || rdl->curs <= 0)
		return ;
	ft_strcpy(rdl->str + curs, rdl->str + curs + 1);
	tgpstr("dl");
	left(rdl->curs + rdl->lpro);
	adv = ft_printf("%s%s ", rdl->prompt, rdl->str);
	left(adv - rdl->lpro - rdl->curs + 1);
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
	int adv;

	if (!rdl->str)
		return ;
	if (rdl->allo == rdl->size)
		rdl_realloc(rdl);
	ft_memmove(rdl->str + rdl->curs + 1, rdl->str + rdl->curs, rdl->size - rdl->curs);
	rdl->str[rdl->curs] = c;
	adv = ft_printf("%s", rdl->str + rdl->curs);
	left(adv - 1);
	rdl->size++;
	rdl->curs++;
}
