/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:23:31 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/06 19:34:29 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "ft_lexer.h"

int	handle_backslash(t_lexer *lx_st)
{
	int		ret;
	char	c[1];

	if (*(lx_st->cursor + 1) == 0)
		return (str_putc(&(lx_st->cursor), &(lx_st->token->data)));
	if (ft_cisin("nrt", *(lx_st->cursor + 1)))
	{
		*c = (*(lx_st->cursor + 1) == 'n') ? '\n' : 0;
		*c = (*(lx_st->cursor + 1) == 't') ? '\t' : *c;
		*c = (*(lx_st->cursor + 1) == 'r') ? '\r' : *c;
		lx_st->cursor += 2;
		return (str_putnstr(c, &lx_st->token->data, 1));
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
	int	ret;

	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	while (42)
	{
		if (*(lx_st->cursor) == '"')
			return (str_putc(&(lx_st->cursor), &(lx_st->token->data))
				== MEMERR) ? MEMERR : handle_common(lx_st);
		else if ((ret = handle_common_inner(lx_st)))
		{
			if (ret == -1)
				continue ;
			return (ret);
		}
		else if (*(lx_st->cursor) == '\0')
		{
			if ((ret = request_new_line(lx_st)))
				return (ret == CTRL_D ? DQUOTE_ERR : ret);
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
				return (ret == CTRL_D ? SQUOTE_ERR : ret);
		}
		else if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
	}
	return (ENDOFINPUT);
}
