/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_core.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:39:07 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/13 01:04:05 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_CORE_H
# define SH_CORE_H

# include "lib/libft.h"
# include "ft_lexer.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>

# define MEMERR 2 
# define SYNERR 3
# define ENVERR 4
# define ACCERR 5


typedef struct			s_redir
{
	struct s_token 		*left;
	struct s_token		*right;
	struct s_token		*op;
	struct s_redir		*next;
}						t_redir;

typedef	struct			s_simple_cmd
{
	struct s_token		*cmd_name;
	struct s_token		*args_lst;
	struct s_token		*assign_lst;
	struct s_redir		*redir_lst;
	struct s_simple_cmd	*next;
}						t_simple_cmd;
/*
	minishell cmd
*/
typedef	struct			s_command
{
	char				**args;
	char				**process_env;
	struct s_command	*next;
	struct s_command	*previous;
}						t_command;

typedef	struct			s_environ
{
	char				*name;
	char				*value;
	struct s_environ	*next;
	struct s_environ	*previous;
}						t_environ;

typedef	int				(*t_builtin)(t_command*);

extern	t_environ		**g_environ;

void					print_tab(char **tab);
void					print_cmd(t_command command);
void					print_cmd_lst(t_command *command);
void					print_env_lst(t_environ *lst);
int						ft_cmptab(char **tab, char *str);
void					free_tab(char **tab);
void					free_tab_bytes(char **tab);
char					**dup_tab(char **tab);
t_command				*new_cmd_node(char **space_split);
void					add_cmdlst(t_command **head, t_command *to_add);
void					free_cmdlst(t_command *command_lst);
void					putstr_stderr(char *str);
int						write_dbuff(t_list *buffer, char c, int *index);
int						putstr_dbuff(t_list *buffer, char *str, int *index);
int						path_access(char *path);
int						ft_ispath(char *str);
char					*handle_pwd_l(void);
void					init_iterator(int *read, int *write);
int						tab_to_lst(char **env, t_environ **env_lst);
char					**lst_to_tab(t_environ *env_lst, int size);
t_environ				*new_env_node(char *name, char *value);
void					add_node(t_environ **head, t_environ *to_add);
char					*get_env_value(char *name);
int						set_shell_env(char *name, char *value);
int						valid_env_name(char *str);
int						valid_env_char(char c);
t_environ				*get_env_node(char *name);
void					delete_env_node(t_environ *to_del);
char					*tab_get_value(char *name, char **env);
char					*get_value(char *env_var);
int						parser(char *line, t_command **cmd_lst);
int						expand_tokens(char **arg);
char					*expand_dollar(char *line);
void					dispatch_parse_err(int error);
int						execute_cmd(t_command *cmd);
int						spawn_bin(t_command *cmd);
char					*searchbin(char *binname, char *path);
int						bin_perm(char *path);
void					exec_error(int errnum, char *str);
int						dir_access(char *cd_path, char **curpath);
void					cleanpath(char *str);
int						add_slash(char **path);
void					cleandotdot(char *path);
int						change_dir(t_command *cmd);
int						ft_env(t_command *cmd);
int						valid_env_var(char *str);
int						append_tab(char **new_env, char **to_add, int count);
int						cd_l(char *curpath, char *arg);
int						cd_p(char *curpath, char *arg);
void					cd_dispatch_err(char *arg, char *curpath);
void					update_env_pwd(char *pwd, char *curpath);
int						cd_error(int errnum, char *str);
char					*getoldpwd(void);
/* wordexp */
typedef struct s_str t_str;
typedef	struct	s_token t_token;
int	ft_wordexp(t_token *word);
int	handle_tilde(t_token *word);
int	handle_exp_param(t_token *word);
int	handle_field_split(t_token *word);
int	quote_removal(t_token *word);
int	insert_str(t_str *word, int *index, char *to_insert);

#endif
