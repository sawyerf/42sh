/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_bang.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:18:48 by apeyret           #+#    #+#             */
/*   Updated: 2019/05/03 17:16:35 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"
#include "readline.h"

extern t_list *g_hst[];

char	*desactivate_bang(char *s)
{
	t_str	str;

	ft_printf("in:   %s\n", s);
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

int		simple_bang(t_lexer *lx_st)
{
	char	*line;
	int		curs;
	t_list	*lst;
	
	g_hst[1] = g_hst[0];
	if (!(lst = hst_getcmp(g_hst[1], "-1")))
		return (1);
	g_hst[1] = NULL;
	curs = lx_st->cursor - lx_st->line;
	line = ft_zprintf("%.*s%s", curs, lx_st->line, lst->content);
	ft_printf("add:  %s\n", line);
	line = desactivate_bang(line);
	ft_printf("des:  %s\n", line);
	line = ft_zprintf("%s%s", line, lx_st->cursor + 2);
	ft_strdel(&lx_st->line);
	lx_st->line = line;
	lx_st->cursor = line + curs;
	ft_printf("line: %s\n", lx_st->line);
	return (0);
}

int		word_bang(t_lexer *lx_st)
{
	char	*s;
	char	c;
	char	d;
	int		i;
	int		curs;
	t_list	*lst;

	c = *lx_st->cursor;
	*lx_st->cursor = 0;
	d = cmdisin(lx_st->line);
	ft_printf("[3]%c\n", c);
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
		return (MEMERR);
	g_hst[1] = g_hst[0]->next;
	if (!(lst = hst_getcmp(g_hst[1], s)))
		return (1);
	g_hst[1] = NULL;
	curs = lx_st->cursor - lx_st->line;
	ft_strdel(&s);
	ft_printf("avant: %s", lx_st->line);
	s = ft_zprintf("%.*s%s", curs, lx_st->line, lst->content);
	ft_printf("add: %s\n", s);
	s = desactivate_bang(s);
	ft_printf("des: %s\n", s);
	s = ft_zprintf("%s%s", s, lx_st->cursor + i + 1);
	ft_strdel(&lx_st->line);
	lx_st->line = s;
	lx_st->cursor = s + curs;
	ft_printf("line: %s\n", lx_st->line);
	return (0);
}

int	handle_bang(t_lexer *lx_st)
{
	ft_printf("[1]\n");
	if (*(lx_st->cursor + 1) == '!')
		return (simple_bang(lx_st));
	else if (!ft_cisin("\n \t", *(lx_st->cursor + 1)) && *(lx_st->cursor + 1))
	{
		ft_printf("[2]\n");
		return (word_bang(lx_st));
	}
	else
		lx_st->cursor++;
	return (0);
}
