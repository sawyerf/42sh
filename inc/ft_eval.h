/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/04 19:27:04 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EVAL_H
# define FT_EVAL_H

# include "sh_core.h"
# include <fcntl.h>

#define PIPEFAIL 20

#define BIN_NO_PATH 1
#define CMD_NOT_FOUND 2
#define BIN_PERM_DENY 3
#define BIN_NOT_FOUND 127 
#define BIN_EXEC_ERR 5
#define	BIN_IS_DIR 6

typedef struct s_redir t_redir;

typedef struct	s_ast_node
{
	t_token_type 	type;
	struct s_simple_cmd	*pipeline;
	int					async;
	int					exit_status;
	struct s_ast_node	*head;
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
	char				**assign_lst;
	t_redir				*redir_lst;
	int					exit_status;
	int					exit_signal; /* -1 if exit normally */
	struct s_cmd_tab	*next;
	struct s_cmd_tab	*previous;
}						t_cmd_tab;

int		eval_tree(t_ast_node *tree);
void	add_to_tree(t_ast_node **head, t_ast_node *to_add);
int		bin_pathfinder(t_cmd_tab *cmd, char *path);
int		spawn_in_pipe(t_cmd_tab *cmd); /* exec without fork, for piping*/
int		spawn_command(t_cmd_tab *cmd); /* fork before exec*/
t_cmd_tab *expand_pipeline(t_simple_cmd *cmd_lst);
int		exec_pipeline(t_ast_node *tree);
void	wait_wrapper(t_cmd_tab *cmd, pid_t pid);
int		is_builtin(t_cmd_tab *cmd);
void	free_cmd_tab(t_cmd_tab *cmd);
void	free_cmd_tab_lst(t_cmd_tab *cmd);
char	**craft_env(char **base_env, char **to_add);
char	*get_process_env(char *key, char **env);
char	**expand_word_lst(t_token *word);
int		handle_redir(t_redir *redir_lst, t_list **head);
int		apply_redir(t_redir *redir, t_list **head);
int		handle_right(int *left_fd, int *right_fd, t_redir *redir);
int		handle_perm(char *cmd_name);
void	exit_wrap(int code, t_cmd_tab *cmd);
int		pathfinder(t_cmd_tab *cmd);
#endif
