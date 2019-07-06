/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_typedef.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <ktlili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:48:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/06 21:03:56 by apeyret          ###   ########.fr       */
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
	DLESS,
	HERE_END,
	HERE_END_QU,
	EOI,
}				t_token_type;

typedef struct		s_lexer
{
	char			*cursor;
	char			*line;
	struct s_token	*token;
	struct s_token	*head;
	int				err;
}					t_lexer;

typedef	struct		s_token
{
	t_token_type	type;
	t_str			data;
	char			**alias;
	struct s_token	*next;
}					t_token;

typedef struct		s_lx_fn
{
	char			c;
	int				(*f)(t_lexer*);
}					t_lx_fn;

#endif
