/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 20:27:49 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/09 20:33:17 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

void	token_to_array(t_token *word, char **array)
{
	int i;

	i = 0;
	while (word)
	{
		array[i] = word->data.str;
		word->data.str = NULL;
		word = word->next;
		i++;
	}
	return ;
}

void	add_cmd_tab(t_cmd_tab **head, t_cmd_tab *to_add)
{
	t_cmd_tab *tmp;

	if (*head == NULL)
		*head = to_add;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		to_add->previous = tmp;
		tmp->next = to_add;
	}
}

void	remove_token(t_simple_cmd *cmd, t_token *todel)
{
	t_token *tmp;

	tmp = todel->next;
	if (todel == cmd->word_lst)
	{
		free_token(todel);
		cmd->word_lst = tmp;
		return ;
	}
	tmp = cmd->word_lst;
	while (tmp->next)
	{
		if (tmp->next == todel)
		{
			tmp->next = todel->next;
			free_token(todel);
			return ;
		}
		tmp = tmp->next;
	}
}

int		is_quoted(char *str)
{
	while (*str)
	{
		if (ft_cisin("'\"\\", *str))
			return (1);
		str++;
	}
	return (0);
}
