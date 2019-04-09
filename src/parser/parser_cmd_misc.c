/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expect_simple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 20:42:11 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/09 20:42:57 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_eval.h"

int	wrapper_free_cmd(int ret, t_parser *parser)
{
	free_simple_cmd(&(parser->cmd));
	return (ret);
}

int	expect_simple_cmd(t_parser *parser)
{
	t_token	*backtrack;
	int		ret;

	ft_bzero(&(parser->cmd), sizeof(t_simple_cmd));
	backtrack = parser->current;
	ret = 0;
	if (!(ret = expect_cmd_pre(parser)))
	{
		if (!(ret = expect_cmd_name(parser)))
			if (((ret = expect_cmd_suffix(parser)) != SYNERR)
					&& (ret))
				return (wrapper_free_cmd(ret, parser));
		return (0);
	}
	else if (!(ret = expect_cmd_name(parser)))
	{
		if (((ret = expect_cmd_suffix(parser)) != SYNERR) && (ret))
			return (wrapper_free_cmd(ret, parser));
		return (0);
	}
	free_simple_cmd(&(parser->cmd));
	parser->current = backtrack;
	return (ret);
}

int	expect_cmd_name(t_parser *parser)
{
	int	ret;

	ret = 0;
	if ((parser->current->type == WORD)
			&& (!parser_is_assign(parser->current)))
	{
		if (ret)
			return (ret);
		if (build_cmd(parser->current, &(parser->cmd)) == MEMERR)
			return (MEMERR);
		if ((ret = next_token(parser)))
			return (ret);
		return (0);
	}
	return (SYNERR);
}

int	expect_cmd_pre(t_parser *parser)
{
	int ret;

	if (((ret = expect_io_redir(parser)) != SYNERR)
		|| ((ret = expect_assign(parser)) != SYNERR))
	{
		if (ret)
			return (ret);
		if (((ret = expect_cmd_pre(parser)) != SYNERR) && (ret))
			return (ret);
		return (0);
	}
	return (SYNERR);
}

int	expect_cmd_suffix(t_parser *parser)
{
	int ret;

	if (((ret = expect_io_redir(parser)) != SYNERR)
		|| ((ret = expect_word(parser)) != SYNERR))
	{
		if (ret)
			return (ret);
		if (((ret = expect_cmd_suffix(parser)) != SYNERR) && (ret))
			return (ret);
		return (0);
	}
	return (SYNERR);
}
