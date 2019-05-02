/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:23:31 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/15 22:42:39 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "ft_lexer.h"

int	handle_backslash(t_lexer *lx_st)
{
	int ret;

	if (*(lx_st->cursor + 1) == 0)
		return (str_putc(&(lx_st->cursor), &(lx_st->token->data)));
	if (*(lx_st->cursor + 1) == 'n')
	{
		lx_st->cursor += 2;
		return (str_putnstr("\n", &lx_st->token->data, 1));
	}
	if (*(lx_st->cursor + 1) == 'r')
	{
		lx_st->cursor += 2;
		return (str_putnstr("\r", &lx_st->token->data, 1));
	}
	if (*(lx_st->cursor + 1) == 't')
	{
		lx_st->cursor += 2;
		return (str_putnstr("\t", &lx_st->token->data, 1));
	}
	if (*(lx_st->cursor + 1) == '\n')
		lx_st->cursor = lx_st->cursor + 2;
	else if ((str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		|| (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR))
		return (MEMERR);
	if (*(lx_st->cursor) == '\0')
	{
		if ((ret = request_new_line(lx_st)))
			return (ret);
	}
	return (0);
}

int	handle_dquote(t_lexer *lx_st)
{
	int ret;

	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	while (42)
	{
		if (*(lx_st->cursor) == '"')
			return (str_putc(&(lx_st->cursor), &(lx_st->token->data))
				== MEMERR) ? MEMERR : handle_common(lx_st);
		else if ((*(lx_st->cursor) == '\\') && (*((lx_st->cursor) + 1)))
		{
			if ((ret = handle_backslash(lx_st)))
				return (ret);
		}
		else if (*(lx_st->cursor) == '\0')
		{
			if ((ret = request_new_line(lx_st)))
				return (ret);
		}
		else if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
	}
	return (ENDOFINPUT);
}

int	handle_squote(t_lexer *lx_st)
{
	int ret;

	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	while (42)
	{
		if (*(lx_st->cursor) == '\'')
		{
			if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
				return (MEMERR);
			return (handle_common(lx_st));
		}
		else if (*(lx_st->cursor) == '\0')
		{
			if ((ret = request_new_line(lx_st)))
				return (ret);
		}
		else if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
	}
	return (ENDOFINPUT);
}
