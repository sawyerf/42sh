/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:25:01 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/10 20:03:42 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"
#include "readline.h"

int	handle_ampersand(t_lexer *lx_st)
{
	if ((*(lx_st->cursor) == '&') && (*(lx_st->cursor + 1) == '&'))
		lx_st->token->type = AND_IF;	
	if ((str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		|| (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR))
		return (MEMERR);
	if (lx_st->token->type == AND_IF)
		return (0);
	return (handle_common(lx_st));
}

int	handle_semic(t_lexer *lx_st)
{
	lx_st->token->type = SEMI_COL;
	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	return (0);
}

int	handle_column(t_lexer *lx_st)
{
	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	if (*(lx_st->cursor) == '|')
	{
		if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
		lx_st->token->type = OR_IF;
	}
	else
		lx_st->token->type = PIPE;
	return (0);
}

int	handle_great(t_lexer *lx_st)
{
	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	lx_st->token->type = GREAT;
	if (*(lx_st->cursor) == '>')
	{
		if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
		lx_st->token->type = DGREAT;
	}
	else if (*(lx_st->cursor) == '&')
	{
		if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
		lx_st->token->type = GREATAND;
	}
	return (0);
}

int	handle_less(t_lexer *lx_st)
{
	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	lx_st->token->type = LESS;
	if (*(lx_st->cursor) == '<')
	{
		if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
		lx_st->token->type = DLESS;
	}
	if (*(lx_st->cursor) == '&')
	{
		if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
		lx_st->token->type = LESSAND;
	}
	return (0);
}
