/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/02 20:35:25 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

t_lx_fn	g_lx_fn[] =\
{
	{'\n', &handle_newline},
	{'0', &handle_digit},
	{'1', &handle_digit},
	{'2', &handle_digit},
	{'3', &handle_digit},
	{'4', &handle_digit},
	{'5', &handle_digit},
	{'6', &handle_digit},
	{'7', &handle_digit},
	{'8', &handle_digit},
	{'9', &handle_digit},
	{'"', &handle_dquote},
	{'&', &handle_ampersand},
	{'\'', &handle_squote},
	{';', &handle_semic},
	{'<', &handle_less},
	{'>', &handle_great},
	{'|', &handle_column},
	{ 0, NULL},
};

static int	dispatch_fn(t_lexer *lx_st)
{
	int i;

	i = 0;
	while (g_lx_fn[i].f)
	{
		if (g_lx_fn[i].c == *(lx_st->cursor))
			return (g_lx_fn[i].f(lx_st));
		i++;
	}
	return (handle_common(lx_st));
}

static void	lex_add_tk(t_lexer *lexer, t_token *tk)
{
	t_token *tmp;

	if (!(lexer->head))
		lexer->head = tk;
	else
	{
		tmp = lexer->head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = tk;
	}
}

void	init_lexer(char *input, t_lexer *lexer_state)
{
	lexer_state->err = 0;
	lexer_state->line = input;
	lexer_state->cursor = input;
}

int			ft_lexer(t_lexer *lexer_state)
{
	lexer_state->head = NULL;
	while (ft_cisin(" \t", *(lexer_state->cursor)))
		lexer_state->cursor = lexer_state->cursor + 1;
	while (*(lexer_state->cursor))
	{
		if (!(lexer_state->token = new_token(0)))
			return (MEMERR);
		lex_add_tk(lexer_state, lexer_state->token);
		if ((lexer_state->err = dispatch_fn(lexer_state)))
			return (lexer_state->err);
		if (lexer_state->token->type == NEWLINE)
			return (0);
		lexer_state->token = NULL;
		while (ft_cisin(" \t", *(lexer_state->cursor)))
			lexer_state->cursor = lexer_state->cursor + 1;
	}
	lex_add_tk(lexer_state, new_token(EOI));
	return (0);
}
