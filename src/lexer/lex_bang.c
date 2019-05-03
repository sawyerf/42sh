/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_bang.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:18:48 by apeyret           #+#    #+#             */
/*   Updated: 2019/05/03 16:40:32 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"
#include "readline.h"

extern t_list *g_hst[];

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
	line = ft_zprintf("%*.s%s%s", curs, lx_st->line, lst->content, lx_st->cursor + 2);
	ft_strdel(&lx_st->line);
	lx_st->line = line;
	lx_st->cursor = line + curs;
	if (!ft_strncmp("!!", line, 2))
	{
		lx_st->cursor += 2;
		return (str_putnstr("!!", &lx_st->token->data, 2));
	}
	return (0);
}

int		word_bang(t_lexer *lx_st)
{
	char	*s;
	int		i;
	int		curs;
	t_list	*lst;

	i = 0;
	s = lx_st->cursor + 1;
	while (*s)
	{
		if (ft_cisin(" \t\n", *s))
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
	ft_strdel(&lx_st->line);
	lx_st->line = s;
	lx_st->cursor = s + curs;
	return (0);
}

int	handle_bang(t_lexer *lx_st)
{
	if (*(lx_st->cursor + 1) == '!')
		return (simple_bang(lx_st));
	else if (!ft_cisin("\n \t", *(lx_st->cursor + 1)) && *(lx_st->cursor + 1))
		return (word_bang(lx_st));
	else
		lx_st->cursor++;
	return (0);
}
