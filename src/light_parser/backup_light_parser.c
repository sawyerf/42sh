/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/02 16:59:18 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_light_parser.h"
#include "ft_eval.h"
/*
int	lp_expect_linebreak(t_light_parser *parser)
{
	(void)parser;
	return (1);	
}

int	lp_expect_separator_op(t_light_parser *parser)
{
	if ((parser->current->type == AMPERS)
		|| (parser->current->type == SEMI_COL))
	{
		parser->current = parser->current->next;
		parser->last_valid = operator;
		return (1);
	}
	return (0);
}

int	lp_expect_separator(t_light_parser *parser)
{
	if (lp_expect_separator_op(parser))
		return (1);
	return (0);

}


int	lp_expect_filename(t_light_parser *parser)
{
	if (parser->current->type == WORD)
	{
		parser->current->type = FILENAME;
		parser->current = parser->current->next;
		parser->last_valid = arg;
		return (1);
	}
	return (0);
}

int	lp_expect_io_file(t_light_parser *parser)
{
	t_token *backtrack;

	backtrack = parser->current;
	if ((parser->current->type >= LESSAND)
		&& (parser->current->type <= GREAT))
	{
		parser->current = parser->current->next;
		parser->last_valid = redir;
		if (lp_expect_filename(parser))
			return (1);
	}
	parser->current = backtrack;
	return (0);
}

int	lp_expect_io_redir(t_light_parser *parser)
{
	t_token *backtrack;

	backtrack = parser->current;
	if (parser->current->type == IO_NUM)
	{
		parser->current = parser->current->next;
		parser->last_valid = redir;
		if (lp_expect_io_file(parser))
			return (1);
	}
	else if (lp_expect_io_file(parser))
		return (1);
	parser->current = backtrack;
	return (0);

}

int	lp_expect_assign(t_light_parser *parser)
{
	if (parser_is_assign(parser->current))
	{
		parser->current->type = ASSIGN;
		parser->current = parser->current->next;
		parser->last_valid = assign;
		return (1);
	}
	return (0);
}

int	lp_expect_cmd_pre(t_light_parser *parser)
{
	if ((lp_expect_io_redir(parser))
		|| (lp_expect_assign(parser)))
	{
		lp_expect_cmd_pre(parser);
		return (1);
	}
	return (0);
}


int	lp_expect_cmd_suffix(t_light_parser *parser)
{
	if ((lp_expect_io_redir(parser))
		|| (lp_expect_word(parser)))
	{
		lp_expect_cmd_suffix(parser);
		return (1);
	}
	return (0);
		
}

int	lp_expect_word(t_light_parser *parser)
{
	if (parser->current->type == WORD)
	{
		parser->current = parser->current->next;
		parser->last_valid = arg;
		return (1);
	}
	return (0);
}

int	lp_expect_cmd_name(t_light_parser *parser)
{
	if ((parser->current->type == WORD)
			&& (!parser_is_assign(parser->current)))
	{   
		parser->current = parser->current->next;
		parser->last_valid = cmd_name;
		return (1);
	}
	return (0);
}

int	lp_expect_simple_cmd(t_light_parser *parser)
{
	t_token 		*backtrack;

	backtrack = parser->current;
	if (lp_expect_cmd_pre(parser))
	{
		if (lp_expect_cmd_name(parser))
			lp_expect_cmd_suffix(parser);
		return (1);
	}
	else if (lp_expect_cmd_name(parser))
	{
		lp_expect_cmd_suffix(parser);
		return (1);
	}
	parser->current = backtrack;	
	return (0);
}

int	lp_expect_pipeline_suffix(t_light_parser *parser)
{
	t_token *backtrack;

	backtrack = parser->current;
	if (parser->current->type == PIPE)
	{
		parser->current = parser->current->next;
		parser->last_valid = operator;
		lp_expect_linebreak(parser);
		if (!lp_expect_simple_cmd(parser))
		{
			parser->current = backtrack;	
			return (0);
		}
		lp_expect_pipeline_suffix(parser);
	}
	return (1);
}

int	lp_expect_pipeline(t_light_parser *parser)
{
	t_token *backtrack;

	backtrack = parser->current;
	if (lp_expect_simple_cmd(parser))
	{
		lp_expect_pipeline_suffix(parser);
		return (1);
	}
	parser->current = backtrack;
	return (0);
}

int	lp_expect_and_or_suffix(t_light_parser *parser)
{
	t_token 		*backtrack;
	backtrack = parser->current;

	if ((parser->current->type == AND_IF)
		|| (parser->current->type == OR_IF))
	{
		parser->current = parser->current->next;
		parser->last_valid = operator;
		lp_expect_linebreak(parser);
		if (!lp_expect_pipeline(parser))
		{
			parser->current = backtrack;
			return (0);
		}
		lp_expect_and_or_suffix(parser);
		return (1);
	}
	return (0);

}

int	lp_expect_and_or(t_light_parser *parser)
{
	t_token *backtrack;
	
	backtrack = parser->current;
	if (lp_expect_pipeline(parser))
	{
		lp_expect_and_or_suffix(parser);
		return (1);
	}
	parser->current = backtrack;
	return (0);
}

int	lp_expect_list_suffix(t_light_parser *parser)
{
	t_token *backtrack;
	
	backtrack = parser->current;
	if (lp_expect_separator_op(parser))
	{
		if (!lp_expect_and_or(parser))
		{
			parser->current = backtrack;
			return (0);
		}
		lp_expect_list_suffix(parser);
	}
	return (1);
}

int	lp_expect_list(t_light_parser *parser)
{
	t_token *backtrack;

	backtrack = parser->current;
	if (lp_expect_and_or(parser))
	{
 		lp_expect_list_suffix(parser);
		return (1);
	}
	parser->current = backtrack;
	return (0);
}

//top level function, no need for backtrack var
int	lp_expect_complete_cmd(t_light_parser *parser)
{	
	if (lp_expect_list(parser))
	{
		if ((lp_expect_separator(parser) || (parser->current->type == NEWLINE)))
			return (1);	
	}
	return (0);
}
*/
t_expecting		is_param(t_token *token)
{
	if (token->data.str[0] != '$')
		return (arg);
	while (token->data.str[i])
	{
		if (!valid_env_char(token->data.str[i])
				return (arg);
	}
	return (param);
}

int		ft_light_parser(char *line, t_autocomplete *autocomplete)
{
	t_token *tokens;
	t_token last_token;
	t_expecting expecting;

	tokens = NULL;
	if (ft_tokenizer_2(line, &tokens) == MEMERR)
		return (MEMERR);
	last_token = tokens;
	expecting = cmd_name;
	while (last_token->type != NEWLINE)
	{
		if ((last_token->type >= PIPE) && (last_token->type <= OR_IF))
		{
			expecting = cmd_name;	
		}
		if (last_token->type == WORD)
		{
			if (expecting == cmd_name)
				expecting = arg;
			else
				expecting = cmd_name;
		}
		last_token = last_token->next;
	}
	if ((last_token->type >= LESSAND) && (last_token->type <= GREAT))
		expecting = arg;
	autocomplete->type = expecting;
	if (last_token->type == WORD)
		autocomplete->str = ft_strdup(last_token->data.str);
	else 
		autocomplete->str = ft_strdup("");
	if (autocomplete->str == NULL)
		return (MEMERR);
	reutnr (0);
}
/*
int		ft_light_parser(t_token *line, t_autocomplete *last)
{
	t_token *tokens;
	t_token last_token;
	t_expecting expecting;

	tokens = NULL;
	if (ft_tokenizer_2(line, &tokens) == MEMERR)
		return (MEMERR);
	last_token = tokens;
	expecting = cmd_name;
	if (last_token->type == NEWLINE)
	{
		last->type = expecting;
		last->str = last_token->data.str;
		return (0);
	}
	while (last_token->type != NEWLINE)
	{
		if ((last_token->type >= PIPE) && (last_token->type <= OR_IF))
		{
			expecting = cmd_name;	
		}
		if (last_token->type == WORD)
		{
			if (expecting = cmd_name)
				expecting = arg;
			else
				expecting = cmd_name;
		}
		last_token = last_token->next;
	}
	if ((last_token->type >= PIPE) && (last_token->type <= OR_IF))
		expecting = cmd_name;
	else if ((last_token->type >= LESSAND) && (last_token->type <= GREAT))
		expecting = arg;
	else if ((last_token->type == WORD)
		expecting = is_param(last_token))
	last->type = expecting;
	last->str = last_token->data.str;
	reutnr (0);
}*/
