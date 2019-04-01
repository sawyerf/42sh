/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wrappers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 11:48:18 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/01 13:14:15 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

void		token_to_array(t_token *word, char **array)
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

char		**expand_word_lst(t_token *word)
{
	size_t	lst_len;
	char	**cmd_av;
	t_token	*iter;
	t_token	*save;

	iter = word;
	while (iter)
	{
		save = iter->next;
		if (ft_wordexp(iter, FT_FALSE) == MEMERR)
			return (NULL);
		iter = save;
	}
	iter = word;
	lst_len = 0;
	while (iter)
	{
		lst_len++;
		iter = iter->next;
	}
	if (!(cmd_av = ft_memalloc((lst_len + 1) * sizeof(char*))))
		return (NULL);
	token_to_array(word, cmd_av);
	return (cmd_av);
}

t_cmd_tab	*expand_simple_cmd(t_simple_cmd *before)
{
	t_cmd_tab *after;

	if (!(after = ft_memalloc(sizeof(t_cmd_tab))))
		return (NULL);
	if (!(after->av = expand_word_lst(before->word_lst)))
		return (NULL);
	if (!(after->assign_lst = expand_word_lst(before->assign_lst)))
		return (NULL);
	after->redir_lst = before->redir_lst;
	return (after);
}

void		add_cmd_tab(t_cmd_tab **head, t_cmd_tab *to_add)
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

t_cmd_tab	*expand_pipeline(t_simple_cmd *cmd_lst)
{
	t_simple_cmd	*iter;
	t_cmd_tab		*cmd_tab;
	t_cmd_tab		*head;

	iter = cmd_lst;
	head = NULL;
	while (iter)
	{
		if (!(cmd_tab = expand_simple_cmd(iter)))
			return (NULL);
		add_cmd_tab(&head, cmd_tab);
		iter = iter->next;
	}
	return (head);
}
