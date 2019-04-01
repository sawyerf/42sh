/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactor_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 19:04:52 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/01 15:56:39 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_eval.h"

int	expect_newline_lst(t_parser *parser)
{
	int ret;

	if (parser->current->type != NEWLINE)
		return (SYNERR);
	while (parser->current->type == NEWLINE)
	{
		if ((ret = next_token(parser)))
			return (ret);
	}
	return (0);
}

int	expect_linebreak_rdl(t_parser *parser)
{
	int ret;

	if (((ret = expect_newline_lst(parser)) != SYNERR)
		&& (ret))
		return (ret);
	if (parser->current->type == EOI)
	{
		if ((ret = request_new_line(parser->lx_state)))
			return (ret);
		return (next_token(parser));
	}
	return (0);
}

int	expect_linebreak(t_parser *parser)
{
	int ret;

	if ((ret = expect_newline_lst(parser)) != SYNERR)
		return (ret);
	return (0);
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

/* unused for now
*/

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

int	expect_filename(t_parser *parser)
{
	int ret;
	// expand stuff here, see posix rule 2

	if (parser->current->type == WORD)
	{
		parser->current->type = FILENAME;
		if (build_redir(parser->current, &(parser->current_redir)) == MEMERR)
			return (MEMERR);
		if ((ret = next_token(parser)))
			return (ret);
		return (0);
	}
	return (SYNERR);
}

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

/*to move*/

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
			if ((ret = expect_cmd_suffix(parser)) != SYNERR)
				return (wrapper_free_cmd(ret, parser));
		if (ret != SYNERR)
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

int	expect_list_suffix(t_parser *parser)
{
	t_token *backtrack;
	int		ret;

	backtrack = parser->current;
	if (!(ret = expect_separator_op(parser)))
	// this generates extra token
	{
		if ((ret = expect_and_or(parser)))
		{
			parser->current = backtrack;
			remove_last_node(parser);
			return (ret);
		}
		if ((ret = expect_list_suffix(parser)) != SYNERR)
			return (ret);
		return (0);
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
		if (((ret = expect_separator_op(parser)) != SYNERR)
			&& (ret))
			return (ret);
		if (((ret = expect_newline_lst(parser)) != SYNERR)
			&& (ret))
			return (ret);
		if (parser->current->type == EOI)
		{
			return (execute_cmdline(parser));
		}
		return (SYNERR);
	}
	return (ret);
}

/*
int expect_complete_cmds_suffix(t_parser *parser)
{
	t_token *backtrack;
	int		ret;

	backtrack = parser->current;
	if (!(ret = expect_newline_lst(parser)))
	{
		if ((ret = tree_add_nl(parser)))
			return (ret);
		execute_cmdline(parser);
		if ((expect_complete_cmd(parser)))
		{
			parser->current = backtrack;
			return (ret);
		}
		if ((ret = expect_complete_cmds_suffix(parser)) != SYNERR)
			return (ret);
		return (0);
	}
	return (ret);
}

int expect_complete_cmds(t_parser *parser)
{
	int ret;

	if (((ret = expect_linebreak(parser)) != SYNERR) && (ret))
		return (ret);
	if (!(ret = expect_complete_cmd(parser)))
	{
		if (((ret = expect_complete_cmds_suffix(parser)) != SYNERR)
			&& (ret))
			return (ret);
		if (((ret = expect_linebreak(parser)) != SYNERR)
			&& (ret))
			return (ret);
		if (parser->current->type == EOI)
			return (0);
		return (SYNERR);
	}
	return (ret);
}*/
