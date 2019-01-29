/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/01/29 12:00:11 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_lexer.h"

t_token	*new_token(int	type)
{
	t_token *new;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (NULL);
	if (!(new->data.str = ft_memalloc(INPUTSZ * sizeof(char))))
		return (NULL);
	new->data.size = INPUTSZ;
	new->type = type;
	return (new);	
}

void	free_token_lst(t_token *token)
{
	t_token *save;

	save = token;
	while (token)
	{
		save = token->next;
		free_token(token);
		token = save;
	}
}

void	free_token(t_token *token)
{
	if (token->data.str)
		free(token->data.str);
	free(token);
}

t_token	*dup_token(t_token *token)
{
	t_token *new;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (NULL);
	ft_memcpy(new, token, sizeof(t_token));
	if (!(new->data.str = ft_strdup(token->data.str)))
		return (NULL);
	new->next = NULL;
	return (new);
}

int	str_putnstr(char *str, t_str *data, size_t n)
{
	char *ptr;

	ptr = str;

	while ((*str) && (n))
	{
		n--;
		if (str_putchar(&str, data) == MEMERR)
			return (MEMERR);
	}
	return (0);
}

int	str_putchar(char **c, t_str *data)
{
	size_t i;

	i = data->len;
	data->str[i] = **c;
	*c = *c + 1;
	data->len = i + 1;
	if (data->len == data->size)
		if (ft_str_realloc(data, INPUTSZ) == MEMERR)
			return (MEMERR);
	return (0);	
}
/*
int	str_putchar(char c, t_str *data)
{
	size_t i;

	i = data->len;
	data->str[i] = c;
	data->len = i + 1;
	if (data->len == data->size)
		if (ft_str_realloc(data, INPUTSZ) == MEMERR)
			return (MEMERR);
	return (0);	
}
*/
/*
this has to be change to is_whitespace
*/
int	ft_is_whitespace(char c)
{
	static char *ifs = "\n\t ";

	int			i;

	i = 0;
	while (ifs[i])
	{
		if (ifs[i] == c)
			return (1);
		i++;
	}
	return (0);
}
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

void	add_token(t_token **head, t_token *to_add)
{
	t_token *tmp;

	tmp = *head;
	if (*head == NULL)
		*head = to_add;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = to_add;	
	}
}

/*
int	ft_tokenizer(char *line, t_token **head)
{
	static	t_func	table[TABLESZ];
	static	int		flag = 0;
	static	char	*input = NULL;
	int				ret;
	t_token			*tmp;

	if (!flag)
		init_jump_table(table);
	if (!input)
		input = line;
	flag = 1;
	*head = NULL;
	while (*line)
	{
		tmp = new_token(0);
		if (!tmp)
			return (NULL);
		if ((ret = table[(int)*line](&line, tmp)) != 0)
			return (ret);	
		add_token(head, tmp);
		while (ft_is_whitespace(*line))
			line++;
	}
	return (0);
}
*/
/*
int next_token(char **line, t_token *token)
{
	static char 	*iter = NULL;
	static	t_func	table[TABLESZ] = {NULL};
	int				ret;

	if (!table[0])
		init_jump_table(table);
	if ((*line) || (!iter))
		iter = *line;	
	while (ft_is_whitespace(*iter))
			iter++;
	if (*iter)
	{
		ret = table[(int)*iter](&iter, token);	
		*line = iter;	
		return (ret);
	}
	*line = iter;	
	iter = NULL;
	token->type = NEWLINE;
	return (ENDOFINPUT);
}

int next_token(char **line, t_token **head)
{
	static char 	*iter = NULL;
	static	t_func	table[TABLESZ] = {NULL};
	t_token 		*token;
	int				ret;

	if (!table[0])
		init_jump_table(table);
	if ((!iter) | (line != NULL))
		iter = *line;	
	if (!(token = new_token(0)))
		return (MEMERR);
	while (ft_is_whitespace(*iter))
			iter++;
	if (*iter)
	{
		ret = table[(int)*iter](&iter, token);	
		add_token(head, token);
		*line = iter;	
		return (ret);
	}
	*line = iter;	
	iter = NULL;
	token->type = NEWLINE;
	add_token(head, token);
	return (ENDOFINPUT);
}
*/

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
