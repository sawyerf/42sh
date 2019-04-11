/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 22:20:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/05 17:51:12 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

void	init_jump_table(t_func table[TABLESZ])
{
	size_t		i;
	static int	flag = 0;

	i = 0;
	if (flag)
		return ;
	flag = 1;
	while (i < TABLESZ)
	{
		if ((i < 58) && (i > 47))
			table[i] = handle_digit;
		else
			table[i] = handle_common;
		i++;
	}
	table[34] = handle_dquote;
	table[38] = handle_ampersand;
	table[39] = handle_squote;
	table[59] = handle_semic;
	table[60] = handle_less;
	table[62] = handle_great;
	table[124] = handle_column;
}

void	init_rev_lex(t_lexer *lex, char *line)
{
	lex->line = line;
	lex->cursor = line;
}

int		rev_lex(char *line, t_token **head)
{
	t_lexer			lexer_state;
	static t_func	table[TABLESZ];

	init_rev_lex(&lexer_state, line);
	init_jump_table(table);
	*head = NULL;
	while (ft_is_whitespace(*(lexer_state.cursor)))
		lexer_state.cursor = lexer_state.cursor + 1;
	while (*(lexer_state.cursor))
	{
		if (!(lexer_state.token = new_token(0)))
			return (MEMERR);
		if (*(lexer_state.cursor) > 0)
			table[(int)*(lexer_state.cursor)](&lexer_state);
		else
			table[1](&lexer_state);
		add_token(head, lexer_state.token);
		if (lexer_state.token->type > ASSIGN)
			break ;
		lexer_state.token = NULL;
		while (ft_is_whitespace(*(lexer_state.cursor)))
			lexer_state.cursor = lexer_state.cursor + 1;
	}
	add_token(head, new_token(1));
	return (0);
}
