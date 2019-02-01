/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/01 18:58:28 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EVAL_H
# define FT_EVAL_H

# include "sh_core.h"

#define PIPEFAIL 20

#define BIN_NO_PATH 1
#define CMD_NOT_FOUND 2
#define BIN_PERM_DENY 3
#define BIN_NOT_FOUND 4
#define BIN_EXEC_ERR 5
#define	BIN_IS_DIR 6

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

int		bin_pathfinder(t_cmd_tab *cmd, char *path);
int		execute_command(t_cmd_tab *cmd); /* exec without fork, for piping*/
int		spawn_command(t_cmd_tab *cmd); /* fork before exec*/
int		eval_tree(t_ast_node *tree);
void	add_to_tree(t_ast_node **head, t_ast_node *to_add);
#endif
