/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/02 20:07:51 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEXER_H
# define FT_LEXER_H

#include "sh_core.h"
#include "ft_parser_typedef.h"
// to delete
#define DQUOTE_ERR 10
#define SQUOTE_ERR 11
//
#define QUOTE_ERR 10
#define BAD_SUB	12
#define INCOMPLETE_SUB 13
#define ENDOFINPUT 14 


#define INPUTSZ 1
#define TABLESZ 128

typedef int (*t_func)(t_lexer*);

void	init_lexer(char *input, t_lexer *lexer_state);

int	handle_newline(t_lexer *lexer_state);
int handle_dquote(t_lexer *lexer_state);
int handle_digit(t_lexer *lexer_state);
int handle_common(t_lexer *lexer_state);
int handle_ampersand(t_lexer *lexer_state);
int handle_squote(t_lexer *lexer_state);
int handle_semic(t_lexer *lexer_state);
int handle_less(t_lexer *lexer_state);
int handle_great(t_lexer *lexer_state);
int handle_column(t_lexer *lexer_state);

/*t_str functions*/
int	str_putnstr(char *str, t_str *data, size_t n);
int	str_putc(char **c, t_str *data);
int	ft_str_realloc(t_str *str_st, size_t newsz);


/*random util functions*/
int	ft_is_whitespace(char c);

void	add_token(t_token **head, t_token *to_add);
t_token	*dup_token(t_token *token);
t_token	*new_token(int type);


/* lexer */
int ft_lexer(t_lexer *lexer_state);
/**/
int			test_lexer(char *line);
t_token		*next_tok(char *line, t_parser *parser);
t_token		*ft_tokenizer(char *line);
int			ft_tokenizer_2(char *line, t_token **head);
//int	next_token(char **line, t_token *token);
/* for light parser*/
int	rev_lex(char *line, t_token **head);

#endif
