/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_history.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 13:41:29 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/12 18:07:32 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

extern t_list *g_hst[4];

t_key	g_khst[] =\
{
	{K_BSPC, &hstdelcara},
	{K_ENTR, &k_hstret},
	{K_ENTD, &k_hstret},
	{K_LEFT, &finish},
	{K_RGHT, &finish},
	{K_CTRC, &k_hstret},
	{K_CTRD, &k_hstret},
	{K_CTRR, &hstnchc},
	{K_TAB, &hstnchc},
	{NULL, &del_cara}
};

int		hstdelcara(t_rdl *rdl, char *buf)
{
	(void)buf;
	int	curs;

	curs = rdl->curs - 1;
	if (curs > rdl->size || rdl->size < 0 ||
		(curs < rdl->curs && rdl->curs <= 0)
		|| (curs >= rdl->curs && rdl->size == curs))
		return (0);
	ft_strcpy(rdl->str + curs, rdl->str + curs + 1);
	rdl->size--;
	if (curs < rdl->curs)
		rdl->curs--;
	hstchc(rdl->str);
	return (0);
}

int		k_hstret(t_rdl *rdl, char *buf)
{
	(void)buf;
	if (!ft_strcmp(K_ENTR, buf))
		return (rdl->str[0] ? 2 : 1);
	else if (!ft_strcmp(K_CTRC, buf))
		return (4);
	else if (!ft_strcmp(K_CTRD, buf))
		return (rdl->str[0] ? 1 : 3);
	return (0);
}

int		history(t_rdl *rdl, char *buf)
{
	char	*new;

	new = NULL;
	if (!ft_strcmp(K_UP, buf))
		new = hstnext(rdl->str);
	else if (!ft_strcmp(K_DOWN, buf))
		new = hstprev();
	if (!new)
		return (0);
	rdlreplace(rdl, new);
	return (0);
}
