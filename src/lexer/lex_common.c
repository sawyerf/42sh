/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_common.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 20:00:58 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 20:04:40 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

int	brackets_param(t_lexer *lx_st)
{
	int ret;

	if (((*(lx_st->cursor) == 0) || (*(lx_st->cursor) == '}'))
		&& (!special_params(*(lx_st->cursor))))
		return (BAD_SUB);
	while ((valid_sup_exp(*(lx_st->cursor)))
		|| (special_params(*(lx_st->cursor))))
	{
		if (*(lx_st->cursor) == '"')
		{
			if ((ret = handle_dquote_param(lx_st)))
				return (ret);
		}
		else if (*(lx_st->cursor) == '\'')
		{
			if ((ret = handle_squote_param(lx_st)))
				return (ret);
		}
		else if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
	}
	if (*(lx_st->cursor) != '}')
		return (BAD_SUB);
	return (!str_putc(&(lx_st->cursor), &(lx_st->token->data)) ? 0 : MEMERR);
}

int	handle_param_exp(t_lexer *lx_st)
{
	int ret;

	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	if (special_params(*(lx_st->cursor)))
		return (str_putc(&(lx_st->cursor), &(lx_st->token->data)));
	if (*(lx_st->cursor) == '{')
	{
		if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
		if ((ret = brackets_param(lx_st)))
			return (ret);
	}
	return (0);
}

int	handle_common_inner(t_lexer *lx_st)
{
	int ret;

	ret = -1;
	if (*(lx_st->cursor) == '$')
		ret = handle_param_exp(lx_st);
	else if (*(lx_st->cursor) == '\\')
		ret = handle_backslash(lx_st);
	else if (*(lx_st->cursor) == '!')
		ret = handle_bang(lx_st);
	else if (!ft_strncmp(lx_st->cursor, "[!", 2))
	{
		if ((str_putc(&(lx_st->cursor), &(lx_st->token->data)))
			|| (str_putc(&(lx_st->cursor), &(lx_st->token->data))))
			return (MEMERR);
	}
	else
		return (0);
	if (!ret)
		return (-1);
	return (ret);
}

int	handle_common(t_lexer *lx_st)
{
	int ret;

	while (*(lx_st->cursor))
	{
		if ((*(lx_st->cursor) == '"') && ((ret = handle_dquote(lx_st))))
			return (ret);
		else if ((*(lx_st->cursor) == '\'') && ((ret = handle_squote(lx_st))))
			return (ret);
		else if ((ret = handle_common_inner(lx_st)))
		{
			if (ret == -1)
				continue;
			return (ret);
		}
		else if ((ft_cisin("\n\t& |><;", *(lx_st->cursor)))
			|| (!*lx_st->cursor))
			break ;
		else if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
	}
	return (0);
}
