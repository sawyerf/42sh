/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_param_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:29:00 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/06 19:34:31 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "ft_lexer.h"

int	handle_dquote_param(t_lexer *lx_st)
{
	int	ret;

	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	while (42)
	{
		if (*(lx_st->cursor) == '"')
			return (str_putc(&(lx_st->cursor), &(lx_st->token->data))
				== MEMERR) ? MEMERR : 0;
		else if ((ret = handle_common_inner(lx_st)))
		{
			if (ret == -1)
				continue ;
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

int	handle_squote_param(t_lexer *lx_st)
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
			return (0);
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
