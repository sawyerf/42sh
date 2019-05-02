/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordexp.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:04:30 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/12 14:47:33 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WORDEXP_H
# define FT_WORDEXP_H

# include "sh_core.h"

# define IFS_WSPACE 1
# define IFS_REG 2

typedef struct s_str	t_str;
typedef	struct s_token	t_token;

int		handle_ifs(t_token **word, char **cursor, char *value, char *ifs);
int		c_insert_str(t_token *word, char *cursor, char *to_insert);
char	*c_next_bslash(char *cursor);
char	*c_next_dquote(char *cursor);
char	*c_next_squote(char *cursor);
int		split_candidate(char *str, char *ifs);
void	shift_bslash(t_str *str_w, int *index);
char	*expand_ifs(char *ifs);
int		ft_is_ifs(char *ifs, char c);
void	remove_wspace(char *value, char *ifs);
t_token *ft_split_word(char *split_at);
void	inside_dquote_qr(t_str *str_w, int *index);
void	shift_str_left(t_str *str_w, int index);
int		ft_wordexp_heredoc(t_token *word);
int		ft_wordexp(t_token *word, t_bool is_redir);
int		handle_tilde(t_token *word);
int		handle_exp_param(t_token *word, t_bool is_redir);
int		quote_removal(t_token *word);
int		insert_str(t_str *word, int *index, char *to_insert);
int		tilde_valid(char c);
int		expand_tilde(t_str *word, int *index, int add_quote);
char	*ft_next_field(char *value, char *ifs);
int		get_ifs(char **ifs);
void	delete_varname(char *cursor);
void	replace_token(t_token **wd, t_token *wd_2, t_token *ir, char **cursor);

#endif
