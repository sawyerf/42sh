/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parser_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 19:44:17 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 19:47:50 by ktlili           ###   ########.fr       */
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

static bool	is_sep(t_token *t)
{
	if ((t) && (((t->type >= PIPE) && (t->type < LESSAND))
		|| (t->type == NEWLINE)))
		return (true);
	return (false);
}

t_token		*get_last_tk(t_token *t, bool *first_word)
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
			*first_word = (words ? false : true);
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
