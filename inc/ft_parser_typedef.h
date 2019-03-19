/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_typedef.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:48:47 by ktlili            #+#    #+#             */
/*   Updated: 2019/03/19 09:57:32 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_TYPEDEF_H
# define FT_PARSER_TYPEDEF_H

typedef struct			s_redir
{
	struct s_token 		*left;
	struct s_token		*right;
	struct s_token		*op;
	struct s_redir		*next;
}						t_redir;
/*
intermediate datastruct before expansions
*/
typedef struct			s_simple_cmd
{
	struct s_token		*word_lst;
	struct s_token		*assign_lst;
	struct s_redir		*redir_lst;
	struct s_simple_cmd	*next;
}						t_simple_cmd;

typedef struct	s_parser
{
	struct s_lexer		*lx_state;
	struct s_token		*current;
	char				*cursor;
	struct s_token 		*head;	
	t_simple_cmd		cmd;
	t_redir				current_redir;	
	t_simple_cmd 		*pipeline;
	struct s_ast_node	*tree;
}						t_parser;

#endif
