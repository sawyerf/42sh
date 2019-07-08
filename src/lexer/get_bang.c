/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bang.cc                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 20:12:25 by apeyret           #+#    #+#             */
/*   Updated: 2019/07/08 20:16:05 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"
#include "readline.h"

extern t_list *g_hst[];

char	*getbang(t_lexer *lx_st)
{
	char	*s;
	char	c;
	char	d;
	int		i;

	c = *lx_st->cursor;
	*lx_st->cursor = 0;
	d = cmdisin(lx_st->line);
	*lx_st->cursor = c;
	i = 0;
	s = lx_st->cursor + 1;
	if (lenint(s))
		return (ft_strndup(lx_st->cursor + 1, lenint(s)));
	while (*s)
	{
		if (ft_cisin(" \t\n", *s) || (*s == d && d == '"'))
			break ;
		i++;
		s++;
	}
	if (!(s = ft_strndup(lx_st->cursor + 1, i)))
		return (NULL);
	return (s);
}

char	*bangjoin(char *line, int curs, char *bang, char *cursor)
{
	char	*s;
	char	*tmp;

	if (!(s = ft_zprintf("%.*s%s", curs, line, bang)))
		return (NULL);
	if (!(tmp = desactivate_bang(s)))
		return (NULL);
	ft_strdel(&s);
	if (!(s = ft_zprintf("%s%s", tmp, cursor)))
		return (NULL);
	ft_strdel(&tmp);
	return (s);
}

int		simple_bang(t_lexer *lx_st)
{
	char	*line;
	int		curs;
	t_list	*lst;

	lst = g_hst[0];
	if (!lst)
		return (BANG_NF);
	curs = lx_st->cursor - lx_st->line;
	if (!(line = bangjoin(lx_st->line, curs,
		(char*)lst->content, lx_st->cursor + 2)))
		return (MEMERR);
	ft_strdel(&lx_st->line);
	lx_st->line = line;
	lx_st->cursor = line + curs;
	return (0);
}

int		word_bang(t_lexer *lx_st)
{
	char	*s;
	int		i;
	int		curs;
	t_list	*lst;

	if (!(s = getbang(lx_st)))
		return (MEMERR);
	i = ft_strlen(s);
	if (!(lst = g_hst[0])
		|| !(lst = hst_getcmp(lst, s)))
	{
		ft_strdel(&s);
		return (BANG_NF);
	}
	ft_strdel(&s);
	curs = lx_st->cursor - lx_st->line;
	if (!(s = bangjoin(lx_st->line, curs,
		(char*)lst->content, lx_st->cursor + i + 1)))
		return (MEMERR);
	ft_strdel(&lx_st->line);
	lx_st->line = s;
	lx_st->cursor = s + curs;
	return (0);
}
