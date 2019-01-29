/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/01/29 15:59:21 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_lexer.h"


int	expect_linebreak(t_parser *parser)
{
	(void)parser;
	return (1);	
}

int	expect_separator_op(t_parser *parser)
{
	if ((parser->current->type == AMPERS)
		|| (parser->current->type == SEMI_COL))
	{
		parser->current = parser->current->next;
		return (1);
	}
	return (0);
}

int	expect_separator(t_parser *parser)
{
	if (expect_separator_op(parser))
		return (1);
	return (0);

}


int	expect_filename(t_parser *parser)
{
/* expand stuff here, see posix rule 2
*/
	if (parser->current->type == WORD)
	{
		parser->current->type = FILENAME;
		if (build_redir(parser->current, &(parser->current_redir)) == MEMERR)
			mem_err_exit(parser);
		parser->current = parser->current->next;
		return (1);
	}
	return (0);
}

int	expect_io_file(t_parser *parser)
{
	t_token *backtrack;

	backtrack = parser->current;
	if ((parser->current->type >= LESSAND)
		&& (parser->current->type <= GREAT))
	{
		if (build_redir(parser->current, &(parser->current_redir)) == MEMERR)
			mem_err_exit(parser);
		parser->current = parser->current->next;
		if (expect_filename(parser))
		{
			return (1);
		}
	}
	parser->current = backtrack;
	return (0);
}

int	expect_io_redir(t_parser *parser)
{
	t_token *backtrack;

	ft_bzero(&(parser->current_redir), sizeof(t_redir));
	backtrack = parser->current;
	if (parser->current->type == IO_NUM)
	{
		if (build_redir(parser->current, &(parser->current_redir)) == MEMERR)
			mem_err_exit(parser);
		parser->current = parser->current->next;
		if (expect_io_file(parser))
		{
			add_redir_lst(&(parser->current_redir), &(parser->cmd.redir_lst));
			return (1);
		}
	}
	else if (expect_io_file(parser))
	{
		add_redir_lst(&(parser->current_redir), &(parser->cmd.redir_lst));
		return (1);
	}
	/*we still need to free redir if we fail*/
	free_redir(&(parser->current_redir));
	parser->current = backtrack;
	return (0);

}

int	expect_assign(t_parser *parser)
{
	if (parser_is_assign(parser->current))
	{
		parser->current->type = ASSIGN;
		if (build_cmd(parser->current, &(parser->cmd)) == MEMERR)
			mem_err_exit(parser);
		parser->current = parser->current->next;
		return (1);
	}
	return (0);
}

int	expect_cmd_pre(t_parser *parser)
{
	if ((expect_io_redir(parser))
		|| (expect_assign(parser)))
	{
		expect_cmd_pre(parser);
		return (1);
	}
	return (0);
}


int	expect_cmd_suffix(t_parser *parser)
{
	if ((expect_io_redir(parser))
		|| (expect_word(parser)))
	{
		expect_cmd_suffix(parser);
		return (1);
	}
	return (0);
		
}

int	expect_word(t_parser *parser)
{
	if (parser->current->type == WORD)
	{
		if (build_cmd(parser->current, &(parser->cmd)) == MEMERR)
			mem_err_exit(parser);
		parser->current = parser->current->next;
		return (1);
	}
	return (0);
}

int	expect_cmd_name(t_parser *parser)
{
	if ((parser->current->type == WORD)
			&& (!parser_is_assign(parser->current)))
	{   
		if (build_cmd(parser->current, &(parser->cmd)) == MEMERR)
			mem_err_exit(parser);
		parser->current = parser->current->next;
		return (1);
	}
	return (0);
}

int	expect_simple_cmd(t_parser *parser)
{
	t_token 		*backtrack;

	ft_bzero(&(parser->cmd), sizeof(t_simple_cmd));
	backtrack = parser->current;
	if (expect_cmd_pre(parser))
	{
		if (expect_cmd_name(parser))
			expect_cmd_suffix(parser);
		return (1);
	}
	else if (expect_cmd_name(parser))
	{
		expect_cmd_suffix(parser);
		return (1);
	}
	parser->current = backtrack;	
	return (0);
}

int	expect_pipeline_suffix(t_parser *parser)
{
	t_token *backtrack;

	backtrack = parser->current;
	if (parser->current->type == PIPE)
	{
		parser->current = parser->current->next;
		expect_linebreak(parser);
		if (!expect_simple_cmd(parser))
		{
			parser->current = backtrack;	
			return (0);
		}
		if (add_to_pipeline(parser) == MEMERR)
			mem_err_exit(parser);
		expect_pipeline_suffix(parser);
	}
	return (1);
}

int	expect_pipeline(t_parser *parser)
{
	t_token *backtrack;

	backtrack = parser->current;
	if (expect_simple_cmd(parser))
	{
		if (add_to_pipeline(parser) == MEMERR)
			mem_err_exit(parser);
		expect_pipeline_suffix(parser);
		return (1);
	}
	parser->current = backtrack;
	return (0);
}

int	expect_and_or_suffix(t_parser *parser)
{
	t_token 		*backtrack;
	t_token_type	op;
	backtrack = parser->current;

	if ((parser->current->type == AND_IF)
		|| (parser->current->type == OR_IF))
	{
		op = parser->current->type;
		parser->current = parser->current->next;
		expect_linebreak(parser);
		if (!expect_pipeline(parser))
		{
			parser->current = backtrack;
			return (0);
		}
		if (((op == AND_IF) && (!parser->exit_status))
			|| ((op == OR_IF) && (parser->exit_status)))
		{
			if (parser_exec_pipe(parser->pipeline) == MEMERR)
				mem_err_exit(parser);
		}
		expect_and_or_suffix(parser);
		return (1);
	}
	return (0);

}

int	expect_and_or(t_parser *parser)
{
	t_token *backtrack;
	
	backtrack = parser->current;
	if (expect_pipeline(parser))
	{
		if (parser_exec_pipe(parser->pipeline) == MEMERR)
			mem_err_exit(parser);
		expect_and_or_suffix(parser);
		return (1);
	}
	parser->current = backtrack;
	return (0);
}

int	expect_list_suffix(t_parser *parser)
{
	t_token *backtrack;
	
	backtrack = parser->current;
	if (expect_separator_op(parser))
	{
		if (!expect_and_or(parser))
		{
			parser->current = backtrack;
			return (0);
		}
		expect_list_suffix(parser);
	}
	return (1);
}

int	expect_list(t_parser *parser)
{
	t_token *backtrack;

	backtrack = parser->current;
	if (expect_and_or(parser))
	{
 		expect_list_suffix(parser);
		return (1);
	}
	parser->current = backtrack;
	return (0);
}

//top level function, no need for backtrack var
int	expect_complete_cmd(t_parser *parser)
{	
	if (expect_list(parser))
	{
		if ((expect_separator(parser) || (parser->current->type == NEWLINE)))
			return (1);	
	}
	return (0);
}
