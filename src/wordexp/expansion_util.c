/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/09 21:45:42 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

int		c_insert_str(t_token *word, char *cursor, char *to_insert)
{
	char	*save;
	int		i;

	i = cursor - (word->data.str);
	word->data.len = ft_strlen(word->data.str);
	while ((word->data.len + ft_strlen(to_insert)) >= word->data.size)
	{
		if (ft_str_realloc(&(word->data), INPUTSZ) == MEMERR)
			return (MEMERR);
	}
	cursor = word->data.str + i;
	if (!(save = ft_strdup(cursor)))
		return (MEMERR);
	ft_memcpy(cursor, to_insert, ft_strlen(to_insert));
	cursor = cursor + ft_strlen(to_insert);
	ft_memcpy(cursor, save, ft_strlen(save) + 1);
	word->data.len = ft_strlen(word->data.str);
	free(save);
	return (0);
}

char	*c_next_bslash(char *cursor)
{
	if ((*cursor != '\0'))
		return (cursor + 1);
	return (cursor);
}

char	*c_next_squote(char *cursor)
{
	cursor++;
	while ((*cursor != 0) && (*cursor != '\''))
		cursor++;
	return (cursor);
}

char	*c_next_dquote(char *cursor)
{
	cursor++;
	while (*cursor != 0)
	{
		if ((*cursor == '"') && (*(cursor - 1) != '\\'))
			break ;
		cursor++;
	}
	return (cursor);
}

int		next_bslash(char *str, int index)
{
	if ((str[index + 1] != '\0'))
		return (index + 1);
	return (index);
}
