/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:01:06 by tduval            #+#    #+#             */
/*   Updated: 2019/07/06 19:18:35 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_patmatch.h"
#include "ft_wordexp.h"

static int	extract_fields(t_token *word, char **fields)
{
	t_token *tmp;
	t_token *head;

	head = NULL;
	while (*fields)
	{
		if (!(tmp = new_token(0)))
			return (MEMERR);
		free(tmp->data.str);
		tmp->data.str = *fields;
		tmp->data.len = ft_strlen(*fields);
		tmp->data.size = tmp->data.len + 1;
		add_token(&head, tmp);
		fields++;
	}
	tmp->next = word->next;
	word->next = head;
	return (0);
}

int			filename_expansion(t_token *word, t_bool is_redir)
{
	char	**fields;
	t_token *tmp;
	t_token *head;

	if (is_redir)
		return (0);
	if (!(fields = ret_matches(word->data.str)))
		return (MEMERR);
	if (ft_strequ(word->data.str, *fields))
	{
		free_tab(fields);
		return (0);
	}
	if (quote_fields(fields) == MEMERR)
		return (MEMERR);
	free(word->data.str);
	word->data.str = *fields;
	word->data.len = ft_strlen(*fields);
	if ((*(fields + 1)))
	{
		if (extract_fields(word, fields + 1) == MEMERR)
			return (MEMERR);
	}
	free(fields);
	return (0);
}
