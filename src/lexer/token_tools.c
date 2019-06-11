/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:31:04 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/09 21:31:23 by ktlili           ###   ########.fr       */
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
