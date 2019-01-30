/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/01/30 17:46:24 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EVAL_H
# define FT_EVAL_H

#include "ft_lexer.h"
#define PIPEFAIL 20

typedef struct			s_tree
{
	void				*tree;
	size_t				size;
	struct s_tree		*left;
	struct s_tree 		*right;
}						t_tree;

/*  simple_cmd after expansions, order is inverted to handle pipes
 */
typedef struct			s_cmd_tab
{
	char	 			*full_path;
	char 				**av;
	char				**exec_env;
	int					exit_status;
	struct s_cmd_exec *next;
}						t_cmd_tab;


typedef struct s_ast_node t_ast_node;

void	add_to_tree(t_ast_node **head, t_ast_node *to_add);
int		tree_add_sep(t_parser *parser);
int		tree_add_and_or(t_parser *parser);
int		tree_add_pipeline(t_parser *parser);

#endif
