/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_complete_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 20:39:19 by ktlili            #+#    #+#             */
/*   Updated: 2019/06/27 13:30:13 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_eval.h"

int	expect_complete_cmds(t_parser *parser)
{
	int ret;

	if (!(ret = expect_newline_lst(parser)))
		if (parser->current->type == EOI)
			return (0);
	return (expect_complete_cmd(parser));
}

int	expect_complete_cmd(t_parser *parser)
{
	int ret;

	if (!(ret = expect_list(parser)))
	{
		if (((ret = expect_newline_lst(parser)) != SYNERR)
			&& (ret))
			return (ret);
		if (parser->current->type == EOI) 
			return (execute_cmdline(parser));
		return (SYNERR);
	}
	return (ret);
}

int	expect_list(t_parser *parser)
{
	t_token *backtrack;
	int		ret;

	backtrack = parser->current;
	if (!(ret = expect_and_or(parser)))
	{
		if ((ret = expect_list_suffix(parser)) != SYNERR)
			return (ret);
		return (0);
	}
	parser->current = backtrack;
	return (ret);
}

int	expect_list_suffix(t_parser *parser)
{
	t_token *backtrack;
	int		ret;

	backtrack = parser->current;
	if (!(ret = expect_separator_op(parser)))
	{
		if ((ret = expect_and_or(parser)))
		{
			if (ret && ret != SYNERR)
				return (ret);
			return (0);
		}
		if ((ret = expect_list_suffix(parser)) != SYNERR)
			return (ret);
		return (0);
	}
	if (ret && ret != SYNERR)
		return (ret);
	return (0);
}
