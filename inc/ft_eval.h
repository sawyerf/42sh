/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/11 23:05:59 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EVAL_H
# define FT_EVAL_H

# include "sh_core.h"
# include <fcntl.h>

# define PIPEFAIL 20

# define BIN_NO_PATH 1
# define CMD_NOT_FOUND 127
# define BIN_PERM_DENY 3
# define BIN_NOT_FOUND 128
# define BIN_EXEC_ERR 5
# define BIN_IS_DIR 6

typedef struct s_redir	t_redir;

typedef struct			s_ast_node
{
	t_token_type		type;
	struct s_simple_cmd	*pipeline;
	int					async;
	int					exit_status;
	struct s_ast_node	*head;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

typedef struct			s_cmd_tab
{
	char				*full_path;
	char				**av;
	char				**process_env;
	char				**assign_lst;
	t_redir				*redir_lst;
	int					exit_status;
	int					exit_signal;
	struct s_cmd_tab	*next;
	struct s_cmd_tab	*previous;
}						t_cmd_tab;

t_cmd_tab				*expand_pipeline(t_simple_cmd *cmd_lst);
void					restore_fd(t_list *to_close);
void					close_save(void);
int						pre_execution(t_cmd_tab *cmd);
int						eval_tree(t_ast_node *tree);
void					add_to_tree(t_ast_node **head, t_ast_node *to_add);
int						bin_pathfinder(t_cmd_tab *cmd, char *path);
int						spawn_in_pipe(t_cmd_tab *cmd);
int						spawn_command(t_cmd_tab *cmd);
int						exec_pipeline(t_ast_node *tree);
void					wait_wrapper(t_cmd_tab *cmd, pid_t pid);
int						is_builtin(t_cmd_tab *cmd);
void					free_cmd_tab(t_cmd_tab *cmd);
void					free_cmd_tab_lst(t_cmd_tab *cmd);
char					**craft_env(char **base_env, char **to_add);
char					*get_process_env(char *key, char **env);
char					**expand_word_lst(t_token *word);
int						handle_redir(t_redir *redir_lst, t_list **head);
int						apply_redir(t_redir *redir, t_list **head);
int						handle_right(int *left_fd, int *right_fd,
							t_redir *redir);
int						handle_perm(char *cmd_name);
void					exit_wrap(int code, t_cmd_tab *cmd);
int						pathfinder(t_cmd_tab *cmd);
void					token_to_array(t_token *word, char **array);
void					add_cmd_tab(t_cmd_tab **head, t_cmd_tab *to_add);
void					remove_token(t_simple_cmd *cmd, t_token *todel);
int						is_quoted(char *str);
t_bool					check_fd(int fd);

#endif
