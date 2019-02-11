/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:10:41 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/11 18:58:02 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_light_parser.h"

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
		if (*(lexer_state.cursor > 0)
			ret = table[(int)*(lexer_state.cursor)](&lexer_state);
		else
			ret = table[1](&lexer_state);
		add_token(head, lexer_state.token);
		if (lexer_state.token > ASSIGN) /* break first op*/
			return (0);
		lexer_state.token = NULL;	
	}
	add_token(head, new_token(1));
	return (0);
}

int fill_autcomp(t_autocomplete *autocomp, t_expecting type, char *str)
{
	autocomp->type = type;
	autocomp->str = ft_strdup(str);
	if (autocomp->str == NULL)
		return (MEMERR);
	return (0);

}

int do_stuff(t_token *start, t_autocomplete *autocomp)
{
	t_expecting expecting;
	int			first_word;

	expecting = cmd_name;
	first_word = 1;
	while (start->type != NEWLINE)
	{
		if (start->type == WORD)
			first_word = 0;

	}
}

int	ft_light_parser(char *line, t_autocomplete *autocomplete)
{
	t_token *tokens;

	ft_strrev(line);
	if (rev_lex(line, &tokens) == MEMERR)
		return (MEMERR);
	if (do_stuff(tokens, autocomplete) == MEMERR)
		return (MEMERR);

}
