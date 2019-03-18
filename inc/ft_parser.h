/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:51:15 by ktlili            #+#    #+#             */
/*   Updated: 2019/03/18 11:50:12 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include "sh_core.h"
# include "ft_lexer.h"
# include "ft_eval.h"

typedef struct s_ast_node t_ast_node;
/* refactor */
int	sh_parser(t_token *start);
int	sh_parser_refac(char *line);
int next_token(t_parser *parser);
/*here doc */
int	handle_here_doc(t_parser *parser);

/* */

int	add_to_pipeline(t_parser *parser);
int	build_redir(t_token *to_add, t_redir *redir);
int	build_cmd(t_token *to_add, t_simple_cmd *cmd);
int	add_redir_lst(t_redir *to_add, t_redir **head);
int		tree_add_nl(t_parser *parser);
int		tree_add_sep(t_parser *parser);
int		tree_add_and_or(t_parser *parser);
int		tree_add_pipeline(t_parser *parser);
// test functions
void	print_token(t_token *t);
void	print_tokens(t_token *start);
void	test_simplecmd(t_simple_cmd *cmd);
void	test_pipeline(t_simple_cmd *start);
void	print_tree(t_ast_node *tree);
void	remove_last_node(t_parser *parser);
//

void	free_simple_cmd(t_simple_cmd *cmd);
void	free_token(t_token *token);
void	free_token_lst(t_token *token);
void	free_redir_lst(t_redir *redir);
void	free_redir(t_redir *redir);
void	free_pipeline(t_simple_cmd *pipeline);
void	free_tree(t_ast_node *tree);
void	mem_err_exit(t_parser *parser);

/*
recursive decent functions 
*/
int	expect_newline_lst(t_parser *parser);
int	expect_linebreak(t_parser *parser);
int	expect_separator_op(t_parser *parser);
int	expect_separator(t_parser *parser);
int	expect_filename(t_parser *parser);
int	expect_io_file(t_parser *parser);
int	expect_here_end(t_parser *parser);
int	expect_io_here(t_parser *parser);
int	expect_io_redir(t_parser *parser);
int	expect_assign(t_parser *parser);
int	expect_cmd_pre(t_parser *parser);
int	expect_word(t_parser *parser);
int	expect_cmd_suffix(t_parser *parser);
int	expect_cmd_name(t_parser *parser);
int	expect_simeple_cmd(t_parser *parser);
int	expect_pipeline_suffix(t_parser *parser);
int	expect_pipeline(t_parser *parser);
int	expect_and_or_suffix(t_parser *parser);
int	expect_and_or(t_parser *parser);
int	expect_list_suffix(t_parser *parser);
int	expect_list(t_parser *parser);
int	expect_complete_cmd(t_parser *parser);
int	expect_complete_cmds_suffix(t_parser *parser);
int	expect_complete_cmds(t_parser *parser);

/*parser util functions */
int	parser_is_assign(t_token const *token);
int	parser_is_name_c(char c);
int next_squote(char *str, int index);
int	next_dquote(char *str, int index);
int	next_bslash(char *str, int index);

#endif
