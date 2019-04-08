/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordexp.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:39:07 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/28 16:42:27 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WORDEXP_H
# define FT_WORDEXP_H

#include "sh_core.h"
/* wordexp */

# define IFS_WSPACE 1
# define IFS_REG 2


typedef struct s_str t_str;
typedef	struct	s_token t_token;

int	handle_ifs(t_token **word, char **cursor, char *value, char *ifs);

int	c_insert_str(t_token *word, char *cursor, char *to_insert);
char	*c_next_bslash(char *cursor);
char	*c_next_dquote(char *cursor);
char	*c_next_squote(char *cursor);
int		split_candidate(char *str, char *ifs);

char *expand_ifs(char *ifs);


void	inside_dquote_qr(t_str *str_w, int *index);
void	shift_str_left(t_str *str_w, int index);
int	ft_wordexp_heredoc(t_token *word);
int	ft_wordexp(t_token *word, t_bool is_redir);
int	handle_tilde(t_token *word);
int	handle_exp_param(t_token *word, t_bool is_redir);
int	handle_field_split(t_token *word);
int	quote_removal(t_token *word);
int	insert_str(t_str *word, int *index, char *to_insert);
int	tilde_valid(char c);
int	expand_tilde(t_str *word, int *index, int add_quote);

#endif
