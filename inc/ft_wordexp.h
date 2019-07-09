/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordexp.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <ktlili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:04:30 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/09 13:55:16 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WORDEXP_H
# define FT_WORDEXP_H

# include "sh_core.h"
# include <stdbool.h>

# define IFS_WSPACE 1
# define IFS_REG 2

typedef struct s_str	t_str;
typedef	struct s_token	t_token;

int		quote_fields(char **fields);
char	*select_exp(char *cursor, char *tmp);
int		handle_exp_param(t_token *word, t_bool is_redir);
int		expand_param(t_token **word, char **cursor,
				char *value, t_bool is_redir);
int		filename_expansion(t_token *word, t_bool is_redir);
char	*exp_sup(char *cursor, bool classic_substitute);
char	*get_var_exp(char *cursor);
char	*substitute_word_if_null(char *cursor, char *zone);
void	sub_error(char *cursor, int err);
bool	lsearch_rev_str(char *str, char *search, int *nb_del);
bool	bsearch_rev_str(char *str, char *search, int *nb_del);
char	*check_second_exp_var(char *zone);
void	print_array(char **array);
char	*substitute_by_len(char *cursor);
char	*quote_str(char *str);
bool	bsearch_str(char *str, char *search, int *nb_del);
bool	lsearch_str(char *str, char *search, int *nb_del);
char	*classic_sub(char *cursor);
char	*assign_sub_var(char *var_name, char *zone);
char	*assign_word_if_null(char *cursor, char *zone);
char	*pattern_matching(char *cursor, char *zone, int mode);
char	*sub_word_if_not_null(char *cursor, char *zone);
char	*test_parameter(char *cursor, char *zone);
bool	lsearch_rev_str(char *str, char *search, int *nb_del);
char	*build_param(char *cursor);
int		handle_ifs(t_token **word, char **cursor, char *value, char *ifs);
int		c_insert_str(t_token *word, char *cursor, char *to_insert);
char	*rev_pattern_matching(char *cursor, char *zone, int mode);
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
size_t	count_dollars(char *str);
char	*ft_next_field(char *value, char *ifs);
int		get_ifs(char **ifs);
void	delete_varname(char *cursor);
void	replace_token(t_token **wd, t_token *wd_2, t_token *ir, char **cursor);
char	*quote_str(char *str);
char	*expand_str(char *cursor);
char	*expand_str_routine(char *cursor, int inside_dquote, t_str result,\
		char *value);
int		expand_classic(t_str *s, char **cursor, char *value);
int		is_expandable(char *cursor, int in_dquote);

#endif
