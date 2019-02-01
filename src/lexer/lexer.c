/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/01 14:10:09 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

#define TABLESZ 128

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


int next_token(char *line, t_token **head)
{
	static char 	*iter = NULL;
	static	t_func	table[TABLESZ] = {NULL};
	t_token 		*token;
	int				ret;

	if (!table[0])
		init_jump_table(table);
	if ((!iter) | (line != NULL))
		iter = line;	
	if (!(token = new_token(0)))
		return (MEMERR);
	while (ft_is_whitespace(*iter))
			iter++;
	if (*iter)
	{
		ret = table[(int)*iter](&iter, token);	
		add_token(head, token);
		return (ret);
	}
	iter = NULL;
	token->type = NEWLINE;
	add_token(head, token);
	return (ENDOFINPUT);
}

t_token	*ft_tokenizer(char *line)
{
	static	t_func	table[TABLESZ];
	static	int		flag = 0;
	t_token			*tmp;
	t_token			*head;
	int				ret;

	if (!flag)
		init_jump_table(table);
	flag = 1;
	head = NULL;
	while (ft_is_whitespace(*line))
		line++;
	while (*line)
	{
		tmp = new_token(0);
		if (!tmp)
			return (NULL);
		if ((*line) > 0 )
			ret = table[(int)*line](&line, tmp);
		else
			ret = table[1](&line, tmp);
		add_token(&head, tmp);
		if (ret)
		{
			ft_printf("21sh: lexer error: %d\n", ret);
			free_token_lst(head);
			return (NULL);
		}
		while (ft_is_whitespace(*line))
			line++;
	}
	add_token(&head, new_token(1));
	return (head);
}

void	ft_test_lexer(char *line)
{
	t_token *head = NULL;
	int ret;
	ret =  next_token(line, &head);
	while (ret != ENDOFINPUT)
		ret = next_token(NULL, &head);
	while (head->type != NEWLINE)
	{

		ft_printf("type %d | str %s\n", head->type, head->data.str);
		head = head->next;
	}

}
