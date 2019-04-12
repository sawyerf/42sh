/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 12:46:44 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/12 15:26:42 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

char		*extract_field(char *value, char *ifs)
{
	int		i;
	char	*next_field;

	i = 0;
	while (ft_is_ifs(ifs, value[i]) == IFS_WSPACE)
		i++;
	if ((ft_is_ifs(ifs, value[i]) == IFS_REG))
	{
		i++;
		ft_memmove(value, value + i, ft_strlen(value + i));
		value[ft_strlen(value + i)] = 0;
		return (ft_strdup(""));
	}
	ft_memmove(value, value + i, ft_strlen(value + i));
	value[ft_strlen(value + i)] = 0;
	if (!(next_field = ft_next_field(value, ifs)))
		return (NULL);
	return (next_field);
}

int			join_token(t_token *word, char *new_field, int before)
{
	char *tmp;

	if ((!before) && (!(tmp = ft_strjoin(word->data.str, new_field))))
		return (MEMERR);
	if ((before) && (!(tmp = ft_strjoin(new_field, word->data.str))))
		return (MEMERR);
	free(word->data.str);
	word->data.str = tmp;
	word->data.len = ft_strlen(tmp);
	word->data.size = ft_strlen(tmp);
	return (0);
}

int			ifs_first_field(t_token **word, char *value, char *ifs)
{
	char	*new_field;
	t_token *tmp;

	if ((ft_is_ifs(ifs, *value)) && ((*word)->data.str[0] != 0))
	{
		if (!(new_field = extract_field(value, ifs)))
			return (MEMERR);
		if (!(tmp = new_token(WORD)))
			return (MEMERR);
		free(tmp->data.str);
		tmp->data.str = new_field;
		tmp->data.len = ft_strlen(new_field);
		tmp->data.size = ft_strlen(new_field);
		(*word)->next = tmp;
	}
	else
	{
		if (!(new_field = extract_field(value, ifs)))
			return (MEMERR);
		if (join_token(*word, new_field, 0) == MEMERR)
			return (MEMERR);
		free(new_field);
	}
	return (0);
}

t_token		*ifs_next_fields(t_token **word, t_token *word_2,
				char *value, char *ifs)
{
	t_token *tmp;
	t_token *iter;
	char	*new_field;

	word_2 = word_2 + 5;
	iter = ((*word)->next != NULL) ? (*word)->next : (*word);
	while (*value)
	{
		if (!split_candidate(value, ifs))
			break ;
		if (!(new_field = extract_field(value, ifs))
			|| (!(tmp = new_token(WORD))))
			return (NULL);
		remove_wspace(value, ifs);
		free(tmp->data.str);
		tmp->data.str = new_field;
		tmp->data.len = ft_strlen(new_field);
		tmp->data.size = ft_strlen(new_field);
		iter->next = tmp;
		iter = tmp;
	}
	return (iter);
}

int			handle_ifs(t_token **word, char **cursor, char *value, char *ifs)
{
	t_token *word_2;
	t_token *last;

	if (!(word_2 = ft_split_word(*cursor)))
		return (MEMERR);
	word_2->next = (*word)->next;
	(*word)->next = NULL;
	if (ifs_first_field(word, value, ifs) == MEMERR)
		return (MEMERR);
	if (!(last = ifs_next_fields(word, word_2, value, ifs)))
		return (MEMERR);
	if (!split_candidate(value, ifs))
	{
		if (join_token(word_2, value, 1) == MEMERR)
			return (MEMERR);
	}
	if (word_2->data.str[0] == 0)
		replace_token(word, word_2, last, cursor);
	else
	{
		last->next = word_2;
		*cursor = word_2->data.str + ft_strlen(value);
		*word = word_2;
	}
	return (0);
}
