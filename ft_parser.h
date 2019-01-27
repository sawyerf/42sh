/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/12 23:14:47 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

#include "ft_lexer.h"

/*
typedef enum	e_non_term
{
	complete_cmd,
	list,
	and_or,
	pipeline,
	simple_cmd,
	cmd_word,
	cmd_pre,
	cmd_suf,
	io_redir,
	io_file,
	filename,
	separator,
	separator_op,
	line_break,
	new_line_lst
}				t_non_term;

typeef	union	u_type
{
	enum e_non_term	terminal;
	enum e_non_term non_terminal;	
}				t_type;
*/

typedef struct	s_parser
{
	struct s_token	*current;
	struct s_token *head;
//	t_ast	**head;
}				t_parser;


/**/
typedef struct s_token t_token;

int	test_sh_parser(t_token *start);
/**/
int	parser_is_assign(t_token const *token);
int	expect_linebreak(t_parser *parser);
int	expect_separator_op(t_parser *parser);
int	expect_separator(t_parser *parser);
int	expect_filename(t_parser *parser);
int	expect_io_file(t_parser *parser);
int	expect_io_redir(t_parser *parser);
int	expect_assign(t_parser *parser);
int	expect_cmd_pre(t_parser *parser);
int	expect_word(t_parser *parser);
int	expect_cmd_suffix(t_parser *parser);
int	expect_cmd_name(t_parser *parser);
int	expect_simeple_cmd(t_parser *parser);
int	expect_pipeline_suffix(t_parser *parser);
int	expect_pipeline(t_parser *parser);
int	expect_or_if_suffix(t_parser *parser);
int	expect_and_if_suffix(t_parser *parser);
int	expect_and_or(t_parser *parser);
int	expect_list_suffix(t_parser *parser);
int	expect_list(t_parser *parser);
int	expect_complete_cmd(t_parser *parser);
//int	expect_(t_parser *parser);
#endif
