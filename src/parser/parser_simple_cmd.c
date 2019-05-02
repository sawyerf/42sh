/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_simple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 20:44:14 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/09 20:54:08 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_eval.h"

int	expect_assign(t_parser *parser)
{
	int ret;

	if (parser_is_assign(parser->current))
	{
		parser->current->type = ASSIGN;
		if (build_cmd(parser->current, &(parser->cmd)) == MEMERR)
			return (MEMERR);
		if ((ret = next_token(parser)))
			return (ret);
		return (0);
	}
	return (SYNERR);
}

int	expect_word(t_parser *parser)
{
	int ret;

	if (parser->current->type == WORD)
	{
		if (build_cmd(parser->current, &(parser->cmd)) == MEMERR)
			return (MEMERR);
		if ((ret = next_token(parser)))
			return (ret);
		return (0);
	}
	return (SYNERR);
}

int	expect_separator_op(t_parser *parser)
{
	int ret;

	if ((parser->current->type == AMPERS)
		|| (parser->current->type == SEMI_COL))
	{
		if ((ret = tree_add_sep(parser)))
			return (ret);
		if ((ret = next_token(parser)))
			return (ret);
		return (0);
	}
	return (SYNERR);
}

int	expect_separator(t_parser *parser)
{
	int ret;

	if (!(ret = expect_separator_op(parser)))
	{
		if ((ret = expect_linebreak(parser)) && (ret != SYNERR))
			return (ret);
		return (0);
	}
	else
		return (ret);
	if (!(ret = expect_newline_lst(parser)))
		return (0);
	return (ret);
}
