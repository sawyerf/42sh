/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:48:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/12 14:27:11 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEXER_TYPEDEF_H
# define FT_LEXER_TYPEDEF_H


typedef	enum	e_token_type
{
	WORD,
	NEWLINE,
	IO_NUM, 
	FILENAME,
	ASSIGN,
	PIPE,
	SEMI_COL,
	AMPERS,
	AND_IF,
	OR_IF,
	LESSAND,
	GREATAND,
	DGREAT,
	LESS,
	GREAT,
}				t_token_type;


typedef struct s_lexer
{
	char *cursor;
	char *line;
	struct s_token *token;
}				t_lexer;

typedef	struct	s_token
{
	t_token_type		type;
	t_str				data;
	struct s_token		*next;	
}				t_token;

#endif
