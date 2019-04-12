/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_ctrlr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:29:28 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/12 18:07:49 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

extern t_list	*g_hst[];
extern t_key	g_khst[];

void	printsearch(t_rdl *hst)
{
	char	*s;

	left(hst, hst->real + hst->lpro);
	if (g_hst[3])
		s = g_hst[3]->content;
	else
		s = NULL;
	tgpstr("cd");
	if (!s)
		hst->vcurs = ft_printf("%s%s': %s", hst->prompt, hst->str, "");
	else
		hst->vcurs = ft_printf("%s%s': %s", hst->prompt, hst->str, s);
	hst->real = hst->vcurs - hst->lpro;
	lastcol(hst);
}

int		hstrouter(t_rdl *hst, char *buf)
{
	int ret;

	if (is_special(buf))
		ret = special_key(hst, buf, g_khst);
	else
	{
		ret = normal_key(hst, buf);
		hstchc(hst->str);
	}
	printsearch(hst);
	return (ret);
}

char	*hstfinal(char *s)
{
	if (g_hst[3] && ft_strstr(g_hst[3]->content, s))
		return (g_hst[3]->content);
	return (NULL);
}

int		ctrlr(t_rdl *rdl, char *str)
{
	char	buf[11];
	int		ret;
	int		stat;
	t_rdl	hst;

	(void)str;
	stat = 0;
	left(rdl, rdl->real + rdl->lpro);
	if (rdlinit(&hst, "(search)`") == MEMERR)
		return (MEMERR + 1);
	printsearch(&hst);
	while ((ret = read(0, &buf, 10)) > 0)
	{
		buf[ret] = 0;
		if ((stat = hstrouter(&hst, buf)) != 0)
			break ;
	}
	ft_printf("\n%s%s", rdl->prompt, rdl->str);
	left(rdl, rdl->size - rdl->curs);
	rdlreplace(rdl, hstfinal(hst.str));
	if (stat == 2 || stat == 4)
		rdladd(rdl, '\n');
	ft_strdel(&hst.str);
	g_hst[3] = NULL;
	return (stat - 1);
}
