/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/01 15:56:45 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EVAL_H
# define FT_EVAL_H

# include "sh_core.h"

#define PIPEFAIL 20


typedef struct s_redir t_redir;

typedef struct	s_ast_node
{
	t_token_type 	type;
	struct s_simple_cmd	*pipeline;
	int					async;
	int					exit_status;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}				t_ast_node;

/* 
 * simple_cmd after expansions, order is inverted to handle pipes
 */
typedef struct			s_cmd_tab
{
	char	 			*full_path;
	char 				**av;
	char				**process_env;
	t_redir				*redir_lst;
	int					exit_status;
	struct s_cmd_tab	*next;
}						t_cmd_tab;


int		execute_cmd(t_cmd_tab *cmd);
int		spawn_bin(t_cmd_tab *cmd);
int		eval_tree(t_ast_node *tree);
void	add_to_tree(t_ast_node **head, t_ast_node *to_add);
#endif
