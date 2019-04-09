/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expect_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 20:45:52 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/09 20:48:48 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_eval.h"

int	expect_io_file(t_parser *parser)
{
	t_token	*backtrack;
	int		ret;

	backtrack = parser->current;
	if ((parser->current->type >= LESSAND)
		&& (parser->current->type <= GREAT))
	{
		if (build_redir(parser->current, &(parser->current_redir)) == MEMERR)
			return (MEMERR);
		if ((ret = next_token(parser)))
			return (ret);
		if ((ret = expect_filename(parser)))
			return (ret);
		return (0);
	}
	parser->current = backtrack;
	return (SYNERR);
}

int	expect_here_end(t_parser *parser)
{
	int ret;

	if (parser->current->type == WORD)
	{
		if ((ret = handle_here_doc(parser)))
			return (ret);
		if (build_redir(parser->current, &(parser->current_redir)) == MEMERR)
			return (MEMERR);
		if ((ret = next_token(parser)))
			return (ret);
		return (0);
	}
	return (SYNERR);
}

int	expect_io_here(t_parser *parser)
{
	t_token *backtrack;
	int		ret;

	backtrack = parser->current;
	if (parser->current->type == DLESS)
	{
		if (build_redir(parser->current, &(parser->current_redir)) == MEMERR)
			return (MEMERR);
		if ((ret = next_token(parser)))
			return (ret);
		if ((ret = expect_here_end(parser)))
			return (ret);
		return (0);
	}
	parser->current = backtrack;
	return (SYNERR);
}

int	wrapper_free_redir(int ret, t_parser *parser)
{
	free_redir(&(parser->current_redir));
	return (ret);
}

int	expect_io_redir(t_parser *parser)
{
	t_token *backtrack;
	int		ret;

	ft_bzero(&(parser->current_redir), sizeof(t_redir));
	backtrack = parser->current;
	if (parser->current->type == IO_NUM)
	{
		if (build_redir(parser->current, &(parser->current_redir)) == MEMERR)
			return (MEMERR);
		if ((ret = next_token(parser)))
			return (wrapper_free_redir(ret, parser));
	}
	if (((ret = expect_io_file(parser)) != SYNERR)
		|| ((ret = expect_io_here(parser)) != SYNERR))
	{
		if (ret)
			return (wrapper_free_redir(ret, parser));
		if (add_redir_lst(&(parser->current_redir), &(parser->cmd.redir_lst)))
			return (wrapper_free_redir(ret, parser));
		return (0);
	}
	free_redir(&(parser->current_redir));
	parser->current = backtrack;
	return (SYNERR);
}
