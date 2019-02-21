/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_history.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 13:41:29 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/20 19:40:54 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_key	g_khst[] =\
{
	{K_BSPC, &del_cara},
	{K_ENTR, &return2},
	{K_LEFT, &finish},
	{K_RGHT, &finish},
	{K_CTRC, &ctrlc},
	{K_CTRD, &ctrlc},
	{NULL,   &del_cara}
};

int		return2(t_rdl *rdl, char *buf)
{
	(void)buf;
	if (!rdl->str[0])
		return (1);
	return (2);
}

void	printsearch(t_rdl *hst)
{
	char	*s;

	left(hst, hst->vcurs + 1);
	tgpstr("cd");
	s = hstchc(hst->str);
	if (!s)
		hst->vcurs = ft_printf("%s%s': %s", hst->prompt, hst->str, "");
	else
		hst->vcurs = ft_printf("%s%s': %s", hst->prompt, hst->str, s);
}

int	hstrouter(t_rdl *hst, char *buf)
{
	int ret;

	if (is_special(buf))
		ret = special_key(hst, buf, g_khst);
	else
		ret = normal_key(hst, buf);
	printsearch(hst);
	return (ret);
}

int		ctrlr(t_rdl *rdl, char *str)
{
	char	buf[11];
	int		ret;
	int		stat;
	t_rdl	hst;

	(void)str;
	stat = 0;
	left(&hst, rdl->curs + rdl->lpro);
	if (rdlinit(&hst, "(search)`") == MEMERR)
		return (MEMERR);
	hst.vcurs = hst.lpro;
	printsearch(&hst);
	while ((ret = read(0, &buf, 10)) > 0)
	{
		buf[ret] = 0;
		if ((stat = hstrouter(&hst, buf)) != 0)
			break;
	}
	ft_printf("\n%s%s", rdl->prompt, rdl->str);
	left(rdl, rdl->size - rdl->curs);
	rdlreplace(rdl, hstchc(hst.str));
	if (stat == 2)
		rdladd(rdl, '\n');
	ft_strdel(&hst.str);
	return (stat - 1);
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
