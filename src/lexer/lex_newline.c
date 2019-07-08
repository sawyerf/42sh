/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 20:01:55 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 20:04:42 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

int	handle_digit(t_lexer *lx_st)
{
	static	char	*ops = "|><;";

	while (*(lx_st->cursor))
	{
		if ((ft_is_whitespace(*(lx_st->cursor)))
			|| (ft_strchr(ops, *(lx_st->cursor))))
		{
			if (ft_strchr("><", *(lx_st->cursor)))
				lx_st->token->type = IO_NUM;
			break ;
		}
		else if (!ft_isdigit(*(lx_st->cursor)))
			return (handle_common(lx_st));
		if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
	}
	return (0);
}

int	handle_newline(t_lexer *lx_st)
{
	lx_st->token->type = NEWLINE;
	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	return (0);
}

int	valid_sup_exp(char c)
{
	if ((c == '_') || (ft_isalnum(c)) || c == ':' || c == '-' || c == '='
		|| c == '?' || c == '+' || c == '#' || c == '%' || c == '/' || c == '['
			|| c == ']' || c == '*' || c == '!' || c == '.' || c == '"'
				|| c == '\'')
		return (1);
	return (0);
}

int	special_params(char c)
{
	if ((c == '?') || (c == '$') || (c == '#') || (c == '!') || (c == '-')
		|| (c == '@'))
		return (1);
	return (0);
}
