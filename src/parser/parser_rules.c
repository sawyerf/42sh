/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/12 23:14:47 by ktlili           ###   ########.fr       */
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
#ifdef DEBUG
	ft_printf("function: %s\n", "sep_op");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	#endif
	if ((parser->current->type == AMPERS)
		|| (parser->current->type == SEMI_COL))
	{
		parser->current = parser->current->next;
		#ifdef DEBUG
		ft_printf("validated sep_op\n");
		#endif
		return (1);
	}
	return (0);
}

int	expect_separator(t_parser *parser)
{
#ifdef DEBUG
	ft_printf("function: %s\n", "sep");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	#endif
	if (expect_separator_op(parser))
		return (1);
	return (0);

}


int	expect_filename(t_parser *parser)
{
/* expand stuff here, see posix rule 2
*/
#ifdef DEBUG
	ft_printf("function: %s\n", "filename");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	#endif
	if (parser->current->type == WORD)
	{
		parser->current->type = FILENAME;
		if (build_redir(parser->current, &(parser->current_redir)) == MEMERR)
			return (MEMERR);
		parser->current = parser->current->next;
		#ifdef DEBUG
		ft_printf("validated filename\n");
		#endif
		return (1);
	}
	return (0);
}

int	expect_io_file(t_parser *parser)
{
	t_token *backtrack;

#ifdef DEBUG
	ft_printf("function: %s\n", "io_file");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	#endif
	backtrack = parser->current;
	if ((parser->current->type >= LESSAND)
		&& (parser->current->type <= GREAT))
	{
		if (build_redir(parser->current, &(parser->current_redir)) == MEMERR)
			return (MEMERR);
		parser->current = parser->current->next;
		if (expect_filename(parser))
		{
			#ifdef DEBUG
			ft_printf("validated io_file\n");
			#endif
			return (1);
		}
	}
	parser->current = backtrack;
	return (0);
}

int	expect_io_redir(t_parser *parser)
{
	t_token *backtrack;

#ifdef DEBUG
	ft_printf("function: %s\n", "io_redir");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	#endif
	ft_bzero(&(parser->current_redir), sizeof(t_redir));
	backtrack = parser->current;
	if (parser->current->type == IO_NUM)
	{
		if (build_redir(parser->current, &(parser->current_redir)) == MEMERR)
			return (MEMERR);
		parser->current = parser->current->next;
		if (expect_io_file(parser))
		{
			#ifdef DEBUG
			ft_printf("validated io_redir\n");
			#endif
			add_redir_lst(&(parser->current_redir), &(parser->cmd.redir_lst));
			return (1);
		}
	}
	else if (expect_io_file(parser))
	{
		#ifdef DEBUG
		ft_printf("validated io_redir\n");
		#endif
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
#ifdef DEBUG
	ft_printf("function: %s\n", "assign");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	#endif
	if (parser_is_assign(parser->current))
	{
		parser->current->type = ASSIGN;
		if (build_cmd(parser->current, &(parser->cmd)) == MEMERR)
			return (MEMERR);
		parser->current = parser->current->next;
		#ifdef DEBUG
		ft_printf("validated assign\n");
		#endif
		return (1);
	}
	return (0);
}

int	expect_cmd_pre(t_parser *parser)
{
#ifdef DEBUG
	ft_printf("function: %s\n", "cmd_pre");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	#endif
	if ((expect_io_redir(parser))
		|| (expect_assign(parser)))
	{
		expect_cmd_pre(parser);
		#ifdef DEBUG
		ft_printf("validated cmd_pre\n");
		#endif
		return (1);
	}
	return (0);
}


int	expect_cmd_suffix(t_parser *parser)
{
#ifdef DEBUG
	ft_printf("function: %s\n", "cmd_suffix");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	#endif
	if ((expect_io_redir(parser))
		|| (expect_word(parser)))
	{
		expect_cmd_suffix(parser);
		#ifdef DEBUG
		ft_printf("validated cmd_suffix\n");
		#endif
		return (1);
	}
	return (0);
		
}

int	expect_word(t_parser *parser)
{
#ifdef DEBUG
	ft_printf("function: %s\n", "word");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	#endif
	if (parser->current->type == WORD)
	{
		if (build_cmd(parser->current, &(parser->cmd)) == MEMERR)
			return (MEMERR);
		parser->current = parser->current->next;
		#ifdef DEBUG
		ft_printf("validated word\n");
		#endif
		return (1);
	}
	return (0);
}

int	expect_cmd_name(t_parser *parser)
{
#ifdef DEBUG
	ft_printf("function: %s\n", "cmd_name");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	#endif
	if ((parser->current->type == WORD)
			&& (!parser_is_assign(parser->current)))
	{   
		//we never get here is current tok is assign so check is redundant ?
		if (build_cmd(parser->current, &(parser->cmd)) == MEMERR)
			return (MEMERR);
		parser->current = parser->current->next;
		#ifdef DEBUG
		ft_printf("validated cmd_name\n");
		#endif
		return (1);
	}
	return (0);
}

int	expect_simple_cmd(t_parser *parser)
{
#ifdef DEBUG
	ft_printf("function: %s\n", "simple_cmd");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	#endif
	t_token 		*backtrack;

	ft_bzero(&(parser->cmd), sizeof(t_simple_cmd));
	backtrack = parser->current;
	if (expect_cmd_pre(parser))
	{
		if (expect_cmd_name(parser))
			expect_cmd_suffix(parser);
		#ifdef DEBUG
		ft_printf("validated simple with pre\n%");
		#endif
		if (add_to_pipeline(parser) == MEMERR)
			return (MEMERR);
		return (1);
	}
	else if (expect_cmd_name(parser))
	{
		expect_cmd_suffix(parser);
		#ifdef DEBUG
		ft_printf("validated simple without pre\n");
		#endif
		if (add_to_pipeline(parser) == MEMERR)
			return (MEMERR);
		return (1);
	}
	parser->current = backtrack;	
	return (0);
}

int	expect_pipeline_suffix(t_parser *parser)
{
#ifdef DEBUG
	ft_printf("function: %s\n", "pipline_suffix");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	#endif
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
		#ifdef DEBUG
		ft_printf("validated pipeline_suffx\n");
		#endif
		expect_pipeline_suffix(parser);
	}
	return (1);
}

int	expect_pipeline(t_parser *parser)
{
#ifdef DEBUG
	ft_printf("function: %s\n", "pipeline");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	#endif
	t_token *backtrack;

	backtrack = parser->current;
	if (expect_simple_cmd(parser))
	{
		expect_pipeline_suffix(parser);
		#ifdef DEBUG
		ft_printf("validated pipeline\n");
		#endif
	//	test_pipeline(parser);
		return (1);
	}
	parser->current = backtrack;
	return (0);
}

int	expect_and_or_suffix(t_parser *parser)
{
#ifdef DEBUG
	ft_printf("function: %s\n", "and_or_suffix");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	#endif
	t_token *backtrack;

	backtrack = parser->current;
	if ((parser->current->type == AND_IF)
		|| (parser->current->type == OR_IF))
	{
		parser->current = parser->current->next;
		expect_linebreak(parser);
		if (!expect_pipeline(parser))
		{
			parser->current = backtrack;
			return (0);
		}
		expect_and_or_suffix(parser);
		#ifdef DEBUG
		ft_printf("validated and_or_suffix\n");
		#endif
		return (1);
	}
	return (0);

}

int	expect_and_or(t_parser *parser)
{
#ifdef DEBUG
	ft_printf("function: %s\n", "and_or");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	#endif
	t_token *backtrack;
	
	backtrack = parser->current;
	if (expect_pipeline(parser))
	{
		expect_and_or_suffix(parser);
#ifdef DEBUG
		ft_printf("validated and_or\n");
		#endif
		return (1);
	}
	parser->current = backtrack;
	return (0);
}

int	expect_list_suffix(t_parser *parser)
{
#ifdef DEBUG
	ft_printf("function: %s\n", "list_suffix");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	#endif
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
	#ifdef DEBUG
	ft_printf("validated list_suffix\n");
	#endif
	return (1);
}

int	expect_list(t_parser *parser)
{
#ifdef DEBUG
	ft_printf("function: %s\n", "list");
	ft_printf("\ttok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	#endif
	t_token *backtrack;

	backtrack = parser->current;
	if (expect_and_or(parser))
	{
 		expect_list_suffix(parser);
		#ifdef DEBUG
		ft_printf("validated list\n");
		#endif
		return (1);
	}
	parser->current = backtrack;
	return (0);
}

//top level function, no need for backtrack var
int	expect_complete_cmd(t_parser *parser)
{	
#ifdef DEBUG
	ft_printf("function: %s\n", "complete_cmd");
	ft_printf("tok: %s| type %d\n==============\n", parser->current->data.str, parser->current->type);
	#endif
	if (expect_list(parser))
	{
		if ((expect_separator(parser) || (parser->current->type == NEWLINE)))
			return (1);	
	}
	return (0);
}
