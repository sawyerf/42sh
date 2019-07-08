/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_core.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <ktlili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:39:07 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 20:26:09 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_CORE_H
# define SH_CORE_H

# include "libft.h"
# include "generic_typedef.h"
# include "ft_lexer_typedef.h"
# include "jobctl_typedef.h"
# include "ft_lexer.h"
# include "ft_parser_typedef.h"
# include "ft_parser.h"
# include "ft_wordexp.h"
# include "ft_eval.h"
# include "ft_light_parser_typedef.h"
# include "ft_light_parser.h"
# include "jobctl.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <stdbool.h>

# define SH_NAME "42sh"
# define SH_VERS "2.0.1"
# define CTRL_D 1
# define CTRL_C 2

# define SYNERR -1
# define ENVERR 4
# define ACCERR 5
# define HEREDOC_ERR 6
# define FDSAVEIN 255
# define FDSAVEOUT 256
# define FDSAVEERR 257
# define BUILTIN 666
# define BUILTIN_FAIL 667

// DEBUG
# include "../logger/incs/logger.h"

# define MODEFILE 2
# define INTERACTIVE 1
# define NONINTERACTIVE 0

typedef struct s_cmd_tab	t_cmd_tab;
typedef	int				(*t_builtin)(t_cmd_tab*);
typedef int				(*t_read_fn)(char*, char**);

typedef struct			s_sh
{
	int					mode;
	int					status;
	int					lastback;
	int					exit_jobs;
	char				**local;
	char				**env;
	char				**alias;
	char				**av;
	int					fd;
	t_job				*job_lst;
	t_job				*current_j;
	t_job				*previous_j;
	struct termios		term_save;
}						t_sh;

typedef	struct			s_sig
{
	int					signum;
	char				*sigstr;
}						t_sig;

extern	t_sh			g_sh;

void					global_del(void);
int						br_print(int err, t_cmd_tab *cmd);
int						request_new_line(t_lexer *lx);
int						run_command(char *line);
int						shlvl(char ***env);
char					*varchr(char **env, char *toto);
char					*envchrr(char **env, char *var);
int						envaddint(char ***env, char *var, int value);
char					*envchrr(char **env, char *var);
t_ast_node				*get_tree(t_ast_node *tree);
int						setenv_wrapper(t_cmd_tab *cmd);
int						ft_set(t_cmd_tab *cmd);
int						ft_unset(t_cmd_tab *cmd);
void					print_env_tab(char **machintruc);
int						ft_cmptab(char **machintruc, char *str);
void					free_tab(char **machintruc);
void					free_tab_bytes(char **machintruc);
char					**dup_tab(char **machintruc);
void					putstr_stderr(char *str);
int						write_dbuff(t_list *buffer, char c, int *index);
int						putstr_dbuff(t_list *buffer, char *str, int *index);
int						path_access(char *path);
int						ft_ispath(char *str);
int						handle_pwd_l(char **pwd);
void					init_iterator(int *read, int *write);
char					*get_env_value(char *name);
int						set_shell_env(char *name, char *value, int to_export);
int						valid_env_name(char *str);
int						valid_env_char(char c);
char					*tab_get_value(char *name, char **env);
char					*get_value(char *env_var);
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
void					update_env_pwd(char *pwd, char *curpath);
char					*getoldpwd(void);
int						csetenv(char ***env, char *var);
char					**envdel(char **env, char *var);
int						envaddstr(char ***env, char *var, char *value);
int						sh_readfile(char *prompt, char **str);
int						missing_quote(char *line);
char					*make_cmdline(t_token *start, t_token *end, int last);
void					del_job(t_job *j);
void					clean_jobs(void);
void					run_script(char *file);
char					*dget_env_value(char *name);

int						cexport(char *var);
int						refresh_jobs(void);
char					*get_termsig(int signum);
void					print_sigexit(t_job *job);
int						exit_jobs(void);
void					shrc(void);
int						readnrun(t_read_fn	read_fn);

#endif
