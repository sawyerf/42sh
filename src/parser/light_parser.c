/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:58:34 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/06 21:23:54 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_light_parser.h"
#include "ft_wordexp.h"


static bool	is_redir(t_token *t)
{
	if ((t) && (t->type >= LESSAND) && (t->type < EOI))
		return (true);
	return (false);
}

static bool is_sep(t_token *t)
{
	if ((t) && (((t->type >= PIPE) && (t->type < LESSAND))
		|| (t->type == NEWLINE)))
		return (true);
	return (false);
}

t_token *get_last_tk(t_token *t, bool *first_word)
{
	t_token *p;
	int		words;

	p = NULL;
	*first_word = true;
	words = 0;
	while ((t) && (t->type != EOI))
	{
		if (t->type == WORD)
		{
			*first_word = (words ?  false : true) ;
			if ((p) && (is_redir(p)))
				*first_word = false;
			words++;
		}
		else if (is_sep(t))
		{
			words = 0;
			*first_word = true;
		}
		p = t;
		t = t->next;	
	}
	return (!p ? t : p);
}

void	extract_last_param(t_autocomplete *autoc)
{
	bool is_param;
	char *s;

	s = autoc->str;
	ft_strrev(s);
	is_param = false;
	while (*s)
	{
		if (*s == '$')
		{
			is_param = true;
			break;
		}
		s++;
	}
	if (is_param)
		*(s + 1) = 0;
	ft_strrev(autoc->str);
	if (!is_param)
		return ;
	autoc->type = param;
}

int	dispatch_autoc(t_token *last, t_autocomplete *autoc,
	bool is_delim, bool first_word)
{
	char *str;

	autoc->type = cmd_name;
	str = "";
	if (last->type >= PIPE) 
	{
		autoc->type = cmd_name;
		if ((last->type >= LESSAND) && (last->type < EOI))
			autoc->type = arg;
		str = "";
	}
	else if (last->type == WORD)
	{
		autoc->type = arg;
		if ((first_word) && (!is_delim))
			autoc->type = cmd_name;
		str = last->data.str;
		if (is_delim)
			str = "";
	}
	if (!(autoc->str = ft_strdup(str)))
		return (MEMERR);
	return (0);
}

int	extract_autoc(t_lexer lex, t_autocomplete *autoc, char *line)
{
	bool	is_delim;
	bool	first_word;
	t_token	*last;

	is_delim = false;
	if ((!lex.err) && (ft_strlen(line))
		&& (ft_cisin(" \n\t\r", lex.line[ft_strlen(line) - 1])))
		is_delim = true;
	last = get_last_tk(lex.head, &first_word);
	if (quote_removal(last) == MEMERR)
		return (MEMERR);
	if (dispatch_autoc(last, autoc, is_delim, first_word) == MEMERR)
	{
		free_token_lst(lex.head);
		return (MEMERR);
	}
	if ((lex.err != SQUOTE_ERR) && (autoc->str[0]))
		extract_last_param(autoc);
	free_token_lst(lex.head);
	return (0);
}

int		ft_light_parser(char *line, t_autocomplete *autoc)
{
	t_lexer lex;
	int		ret;
	int		mode;

	ft_bzero(&lex, sizeof(t_lexer));
	lex.line = line;
	lex.cursor = line;
	mode = g_sh.mode;
	g_sh.mode = NONINTERACTIVE;
	if ((ret = ft_lexer(&lex)) == MEMERR)
	{
		g_sh.mode = mode;
		return (ret);
	}
	g_sh.mode = mode;
	if (extract_autoc(lex, autoc, line) == MEMERR)
		return (MEMERR);
	return (0);
}

