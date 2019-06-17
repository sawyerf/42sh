/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:46:10 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/17 18:18:29 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "sh_core.h"

typedef	struct			s_hash
{
	char				opt[2];
	char				**search;
}						t_hash;

typedef	struct			s_fc
{
	char				opt[6];
	char				*editor;
	char				*range[2];
	char				*by;
	char				*to;
}						t_fc;

typedef void	(*t_job_print)(t_job*);

t_job					*jobs_conv_pct(char *s);
t_job					*jobs_conv_min(char *s);
t_job					*jobs_conv_num(char *s);
t_job					*jobs_conv_cmd(char *s);
t_job					*jobs_conv_any(char *s);

int						fg(t_cmd_tab *cmd);
int						bg(t_cmd_tab *cmd);
int						fc(t_cmd_tab *cmd);
int						fc_l(t_fc fc);
int						fc_e(t_fc fc);
int						fc_s(t_fc fc);
int						fc_le(t_fc fc);
char					*fc_filename(t_list *lst, int size);
int						fc_writelst(char *file, t_list *lst, int size);
char					*fc_read(char *file);
int						run_editor(t_fc *fc, char *file);
void					fc_print(t_fc fc, t_list *lst, int i);
int						fc_parser(char **av, t_fc *fc);
void					run_script(char *file);
int						fc_rangel(t_fc fc, t_list **beg, int *i);
int						fc_rangee(t_fc fc, t_list **beg, int *i);
int						fc_rangele(t_fc fc, t_list **beg, int *i);
void					fc_del(t_fc *fc);
int						hash(t_cmd_tab *cmd);
int						parser_takeopt(char *opt, char *arg, char *in,
							char *name);
int						cd_l(char *curpath, char *arg);
int						cd_p(char *curpath, char *arg);
int						cd_dispatch_err(char *arg, char *curpath);
int						cd_error(int errnum, char *str);
int						change_dir(t_cmd_tab *cmd);

int						ft_echo(t_cmd_tab *cmd);

int						type(t_cmd_tab *cmd);

int						ft_exit(t_cmd_tab *cmd);
int						ft_env(t_cmd_tab *cmd);
int						ft_unsetenv(t_cmd_tab *cmd);
int						jobs(t_cmd_tab *cmd);
void					jobs_print_l(t_job *j);
int						jobs_print_all(t_job_print jobs_printer);
t_job					*jobs_conv_pct(char *s);
t_job					*jobs_conv_num(char *s);
t_job					*jobs_conv_min(char *s);
t_job					*jobs_conv_cmd(char *s);
t_job					*jobs_conv_any(char *s);
t_job					*jobs_conversion(char *arg);
int						export(t_cmd_tab *cmd);

int						alias(t_cmd_tab *cmd);
int						unalias(t_cmd_tab *cmd);
int		valid_alias(char *s);
#endif
