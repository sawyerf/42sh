/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/04 13:50:36 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEXER_H
# define FT_LEXER_H

#include "sh_core.h"

#define DQUOTE_ERR 10
#define SQUOTE_ERR 11
#define BAD_SUB	12
#define INCOMPLETE_SUB 13
#define ENDOFINPUT 14 


#define INPUTSZ 24

/*
Lexer jump table
*/
typedef int (*t_func)(char**, t_token*);

int handle_dquote(char **input, t_token *token);
int handle_digit(char **input, t_token *token);
int handle_common(char **input, t_token *token);
int handle_ampersand(char **input, t_token *token);
int handle_squote(char **input, t_token *token);
int handle_semic(char **input, t_token *token);
int handle_less(char **input, t_token *token);
int handle_great(char **input, t_token *token);
int handle_column(char **input, t_token *token);

/*
	intermediate cmd functions
*/
/*t_str functions*/
int	str_putnstr(char *str, t_str *data, size_t n);
int	str_putchar(char **c, t_str *data);
int	ft_str_realloc(t_str *str_st, size_t newsz);


/*random util functions*/
int	ft_is_whitespace(char c);

void	add_token(t_token **head, t_token *to_add);
t_token	*dup_token(t_token *token);
t_token	*new_token(int type);


/* lexer */
t_token	*ft_tokenizer(char *line);
//int	next_token(char **line, t_token *token);
int	next_token(char *line, t_token **head);

#endif
