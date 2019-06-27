/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_separator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:28:03 by ktlili            #+#    #+#             */
/*   Updated: 2019/06/27 13:30:15 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_eval.h"


int	expect_separator_op(t_parser *parser)
{
	int ret;

	if ((parser->current->type == AMPERS)
		|| (parser->current->type == SEMI_COL)
			|| (parser->current->type == NEWLINE))
	{
		if ((ret = tree_add_sep(parser)))
			return (ret);
		if ((ret = next_token(parser)))
			return (ret);
		if ((ret = expect_newline_lst(parser)) && (ret != SYNERR))
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
