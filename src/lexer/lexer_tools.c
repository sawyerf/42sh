/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:35:55 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/01 13:44:34 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

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

t_token	*new_token(int type)
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
	if (!(new->data.str = ft_memalloc(token->data.size)))
		return (NULL);
	ft_strcpy(new->data.str, token->data.str);
	new->next = NULL;
	return (new);
}

int		str_putnstr(char *str, t_str *data, size_t n)
{
	while ((*str) && (n))
	{
		n--;
		if (str_putc(&str, data) == MEMERR)
			return (MEMERR);
	}
	return (0);
}

int		str_putc(char **c, t_str *data)
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

int	ft_is_whitespace(char c)
{
	static char	*ws = "\n\t ";
	int			i;

	i = 0;
	while (ws[i])
	{
		if (ws[i] == c)
			return (1);
		i++;
	}
	return (0);
}
