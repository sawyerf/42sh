/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_ctrlr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:29:28 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/06 20:13:34 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

extern t_list	*g_hst[];
extern t_key	g_khst[];

void	printsearch(t_rdl *hst)
{
	char	*s;
	int		size;

	s = hst->str;
	hst->str = hst->paste;
	size = hst->size;
	hst->size = ft_strlen(hst->paste);
	left(hst, hst->real - 1);
	hst->size = size;
	hst->str = s;
	if (g_hst[3])
		s = g_hst[3]->content;
	else
		s = NULL;
	ft_strdel(&hst->paste);
	if (!s)
		hst->paste = ft_zprintf("%s': %s", hst->str, "");
	else
		hst->paste = ft_zprintf("%s': %s", hst->str, s);
	s = hst->str;
	hst->str = hst->paste;
	size = hst->size;
	hst->size = ft_strlen(hst->paste);
	reprint(hst, hst->size);
	hst->real = hst->size;
	hst->size = size;
	hst->str = s;
	lastcol(hst);
}

void	hstaddstr(t_rdl *rdl, char *str)
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
	rdl->curs += len;
}

int		hstrouter(t_rdl *hst, char *buf)
{
	int ret;

	ret = 0;
	if (is_special(buf))
		ret = special_key(hst, buf, g_khst);
	else
	{
		hstaddstr(hst, buf);
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
	ft_strdel(&hst.prompt);
	g_hst[3] = NULL;
	return (stat - 1);
}
