/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_ctrlr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:29:28 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/21 14:59:49 by apeyret          ###   ########.fr       */
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
	s = g_hst[3] ? g_hst[3]->content : NULL;
	ft_strdel(&hst->paste);
	hst->paste = s ? ft_zprintf("%s': %s", hst->str, s)
					: ft_zprintf("%s': %s", hst->str, "");
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
	int		arr[2];
	t_rdl	hst;

	(void)str;
	arr[1] = 0;
	left(rdl, rdl->real + rdl->lpro);
	if (rdlinit(&hst, "(search)`") == MEMERR)
		return (MEMERR + 1);
	printsearch(&hst);
	while ((arr[0] = read(0, &buf, 10)) > 0)
	{
		buf[arr[0]] = 0;
		if ((arr[1] = hstrouter(&hst, buf)) != 0)
			break ;
	}
	ft_printf("\n%s%s", rdl->prompt, rdl->str);
	left(rdl, rdl->size - rdl->curs);
	rdlreplace(rdl, hstfinal(hst.str));
	if (arr[1] == 2 || arr[1] == 4)
		rdladd(rdl, '\n');
	ft_strdel(&hst.str);
	ft_strdel(&hst.prompt);
	ft_strdel(&hst.paste);
	g_hst[3] = NULL;
	return (arr[1] - 1);
}
