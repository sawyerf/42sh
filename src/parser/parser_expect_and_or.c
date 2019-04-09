/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expect_and_or.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 20:40:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/09 20:53:50 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_eval.h"

int	expect_and_or(t_parser *parser)
{
	t_token *backtrack;
	int		ret;

	backtrack = parser->current;
	if (!(ret = expect_pipeline(parser)))
	{
		if ((ret = expect_and_or_suffix(parser)) != SYNERR)
			return (ret);
		return (0);
	}
	parser->current = backtrack;
	return (ret);
}

int	expect_and_or_suffix(t_parser *parser)
{
	t_token *backtrack;
	int		ret;

	backtrack = parser->current;
	if ((parser->current->type == AND_IF)
		|| (parser->current->type == OR_IF))
	{
		if (tree_add_and_or(parser) == MEMERR)
			return (MEMERR);
		if ((ret = next_token(parser)))
			return (ret);
		if (((ret = expect_linebreak_rdl(parser)) != SYNERR)
			&& (ret))
			return (ret);
		if ((ret = expect_pipeline(parser)))
		{
			parser->current = backtrack;
			return (ret);
		}
		if ((ret = expect_and_or_suffix(parser)) != SYNERR)
			return (ret);
		return (0);
	}
	return (SYNERR);
}

int	expect_pipeline(t_parser *parser)
{
	t_token	*backtrack;
	int		ret;

	backtrack = parser->current;
	if (!(ret = expect_simple_cmd(parser)))
	{
		if (add_to_pipeline(parser) == MEMERR)
			return (MEMERR);
		if (((ret = expect_pipeline_suffix(parser)) != SYNERR) && (ret))
			return (ret);
		if (tree_add_pipeline(parser) == MEMERR)
			return (MEMERR);
		return (0);
	}
	parser->current = backtrack;
	return (ret);
}

int	expect_pipeline_suffix(t_parser *parser)
{
	t_token	*backtrack;
	int		ret;

	backtrack = parser->current;
	if (parser->current->type == PIPE)
	{
		if ((ret = next_token(parser)))
			return (ret);
		if (((ret = expect_linebreak_rdl(parser)) != SYNERR)
			&& (ret))
		{
			free_pipeline(parser->pipeline);
			return (ret);
		}
		if ((ret = expect_simple_cmd(parser)))
		{
			parser->current = backtrack;
			return (ret);
		}
		if (add_to_pipeline(parser) == MEMERR)
			return (MEMERR);
		if ((ret = expect_pipeline_suffix(parser)) != SYNERR)
			return (ret);
	}
	return (0);
}
