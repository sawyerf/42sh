/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_bang.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:18:48 by apeyret           #+#    #+#             */
/*   Updated: 2019/05/03 18:34:10 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"
#include "readline.h"

extern t_list *g_hst[];

char	*desactivate_bang(char *s)
{
	t_str	str;

	str.str = NULL;
	while (*s)
	{
		if (*s == '\\')
		{
			str_putnstr(s, &str, 2);
			s += 2;
		}
		else if (*s == '\'')
		{
			while (*s)
			{
				str_putnstr(s, &str, 1);
				s++;
				if (*s == '\'')
				{
					str_putc(&s, &str);
					s++;
					break;
				}
			}
		}
		else if (*s == '!' && !ft_cisin(" \t\n", *s) && *s)
		{
			str_putnstr("\\!", &str, 2);
			s++;
			if (*s == '!')
			{
				str_putnstr("\\!", &str, 2);
				s++;
			}
		}
		else
			str_putc(&s, &str);
	}
	return (str.str);
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
	if (!(lst = hst_getcmp(lst, "-1")))
		return (BANG_NF);
	curs = lx_st->cursor - lx_st->line;
	if (!(line = bangjoin(lx_st->line, curs, (char*)lst->content, lx_st->cursor + 2)))
		return (MEMERR);
	ft_strdel(&lx_st->line);
	lx_st->line = line;
	lx_st->cursor = line + curs;
	return (0);
}

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
	while (*s)
	{
		if (ft_cisin(" \t\n", *s) || (*s == d && d == '"'))
			break;
		i++;
		s++;
	}
	if (!(s = ft_strndup(lx_st->cursor + 1, i)))
		return (NULL);
	return (s);
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
	lst = g_hst[0]->next;
	if (!(lst = hst_getcmp(lst, s)))
		return (BANG_NF);
	curs = lx_st->cursor - lx_st->line;
	ft_strdel(&s);
	if (!(s = bangjoin(lx_st->line, curs, (char*)lst->content, lx_st->cursor + i + 1)))
		return (MEMERR);
	ft_strdel(&lx_st->line);
	lx_st->line = s;
	lx_st->cursor = s + curs;
	return (0);
}

int	handle_bang(t_lexer *lx_st)
{
	int ret;

	ret = 0;
	if (*(lx_st->cursor + 1) == '!')
		ret = simple_bang(lx_st);
	else if (!ft_cisin("\n \t", *(lx_st->cursor + 1)) && *(lx_st->cursor + 1))
		ret = word_bang(lx_st);
	else
		lx_st->cursor++;
	if (!ret)
		ft_printf("%s", lx_st->line);
	return (ret);
}
