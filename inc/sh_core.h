/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_core.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:39:07 by ktlili            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/02/02 15:23:31 by ktlili           ###   ########.fr       */
=======
/*   Updated: 2019/02/06 16:05:39 by ktlili           ###   ########.fr       */
>>>>>>> ktlili
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_CORE_H
# define SH_CORE_H

# include "libft.h"
# include "generic_typedef.h"
# include "ft_lexer_typedef.h"
# include "ft_lexer.h"
# include "ft_parser_typedef.h"
# include "ft_parser.h"
# include "ft_wordexp.h"
# include "ft_eval.h"
# include "ft_light_parser_typedef.h"
# include "ft_light_parser.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>

# define MEMERR 2 
# define SYNERR 3
# define ENVERR 4
# define ACCERR 5



/*
	minishell cmd to remove
*/
typedef	struct			s_command
{
	char				**args;
	char				**process_env;
	struct s_command	*next;
	struct s_command	*previous;
}						t_command;
/*
*/
typedef	struct			s_environ
{
	char				*name;
	char				*value;
	int					to_export;
	struct s_environ	*next;
	struct s_environ	*previous;
}						t_environ;

typedef struct s_cmd_tab t_cmd_tab;

typedef	int				(*t_builtin)(t_cmd_tab*);

extern	t_environ		**g_environ;
t_ast_node				*get_tree(t_ast_node *tree);
int						change_dir(t_cmd_tab *cmd);
int						ft_exit(t_cmd_tab *cmd);
int						ft_env(t_cmd_tab *cmd);
int						ft_unsetenv(t_cmd_tab *cmd);
int						setenv_wrapper(t_cmd_tab *cmd);
int						ft_echo(t_cmd_tab *cmd);

void					print_env_tab(char **tab);
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
int						env_tab_to_lst(char **env, t_environ **env_lst);
char					**lst_to_tab(t_environ *env_lst, int size);
t_environ				*new_env_node(char *name, char *value);
t_environ				*env_to_lst(char *env_var);
void					add_node(t_environ **head, t_environ *to_add);
char					*get_env_value(char *name);
int						set_shell_env(char *name, char *value, int to_export);
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
char					*searchbin(char *binname, char *path);
int						bin_perm(char *path);
void					exec_error(int errnum, char *str);
int						dir_access(char *cd_path, char **curpath);
void					cleanpath(char *str);
int						add_slash(char **path);
void					cleandotdot(char *path);
int						valid_env_var(char *str);
int						append_tab(char **new_env, char **to_add, int count);
int						cd_l(char *curpath, char *arg);
int						cd_p(char *curpath, char *arg);
int						cd_dispatch_err(char *arg, char *curpath);
void					update_env_pwd(char *pwd, char *curpath);
int						cd_error(int errnum, char *str);
char					*getoldpwd(void);

#endif
