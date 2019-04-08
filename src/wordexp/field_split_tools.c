/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:46:34 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/08 17:39:00 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

void	remove_wspace(char *value, char *ifs)
{
	int i;

	i = 0;
	while (ft_is_ifs(ifs, value[i]) == IFS_WSPACE)
		i++;
	ft_memmove(value, value + i, ft_strlen(value + i));
	value[ft_strlen(value + i)] = 0;
}

int		split_candidate(char *str, char *ifs)
{
	int index;

	index = 0;
	while (str[index])
	{
		if (ft_cisin(ifs, str[index]))
			return (1);
		index++;
	}
	return (0);
}

void	replace_token(t_token *word, t_token *new_fields)
{
	t_token			*save;
	t_token_type	type;

	save = word->next;
	type = word->type;
	if (word->data.str)
		free(word->data.str);
	ft_memcpy(word, new_fields, sizeof(t_token));
	word->type = type;
	while (word->next)
		word = word->next;
	word->next = save;
	free(new_fields);
}

char	*expand_ifs(char *ifs)
{
	t_token tmp;

	tmp.type = WORD;
	tmp.data.str = ifs;
	tmp.data.len = ft_strlen(ifs);
	tmp.data.size = ft_strlen(ifs);
	if (ft_wordexp(&tmp, FT_TRUE) == MEMERR)
		return (NULL);
	return (tmp.data.str);
}

t_token	*ft_split_word(char *split_at)
{
	char	*half;
	t_token	*new;

	half = ft_strdup(split_at);
	*split_at = 0;
	if (!(new = new_token(WORD)))
		return (NULL);
	free(new->data.str);
	new->data.str = half;
	new->data.len = ft_strlen(half);
	new->data.size = new->data.len;
	return (new);
}
