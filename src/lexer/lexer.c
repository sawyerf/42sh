/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/15 19:08:44 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"


void	init_jump_table(t_func table[TABLESZ])
{
	size_t i;

	i = 0;

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

int rev_lex(char *line, t_token **head)
{
	t_lexer 			lexer_state;
	static t_func	 	table[TABLESZ];
	static int			flag = 0;

	lexer_state.line = line;
	lexer_state.cursor = line;
	if (!flag)
		init_jump_table(table);
	flag = 1;
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
		if (lexer_state.token->type > ASSIGN) // break first op
			break;
		lexer_state.token = NULL;	
		while (ft_is_whitespace(*(lexer_state.cursor)))
			lexer_state.cursor = lexer_state.cursor + 1;
	}
	add_token(head, new_token(1));
	return (0);
}

t_token	*ft_tokenizer(char *line)
{
	static	t_func	table[TABLESZ];
	static	int		flag = 0;
	t_lexer			lexer_state;
	t_token			*head;
	int				ret;

	lexer_state.line = line;
	lexer_state.cursor = line;
	if (!flag)
		init_jump_table(table);
	flag = 1;
	head = NULL;
	while (ft_is_whitespace(*(lexer_state.cursor)))
		lexer_state.cursor = lexer_state.cursor + 1;
	while (*(lexer_state.cursor))
	{
		lexer_state.token = new_token(0);
		if (!lexer_state.token)
			return (NULL);
		if (*(lexer_state.cursor) > 0 )
			ret = table[(int)*(lexer_state.cursor)](&lexer_state);
		else
			ret = table[1](&lexer_state);
		add_token(&head, lexer_state.token);
		lexer_state.token = NULL;
		if (ret == ENDOFINPUT) /* this is useless */
		{
		//	ft_printf("21sh: lexer error: %d\n", ret);
			free_token_lst(head);
			return (NULL);
		}
		while (ft_is_whitespace(*(lexer_state.cursor)))
			lexer_state.cursor = lexer_state.cursor + 1;
	}
	add_token(&head, new_token(1));
	free(lexer_state.line);
	return (head);
}
