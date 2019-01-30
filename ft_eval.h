/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/01/29 15:43:22 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EVAL_H
# define FT_EVAL_H

#include "ft_lexer.h"

typedef struct s_parser t_parser;

typedef struct			s_cmd_tab
{
	char 	*full_path;
	char 	**av;
	char	**exec_env;
}						t_cmd_tab;

typedef enum	e_tree_node
{
	pipeline = 5,
	semi_col = 6,
	ampers = 7,
	and_if = 8,
	or_if = 9,
}				t_tree_node;

typedef struct s_ast_node t_ast_node;

void	add_to_tree(t_ast_node **head, t_ast_node *to_add);
int		tree_add_sep(t_parser *parser);
int		tree_add_and_or(t_parser *parser);
int		tree_add_pipeline(t_parser *parser);

#endif
