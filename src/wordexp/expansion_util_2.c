/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_util_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:34:39 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/09 21:45:59 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

int		ft_is_ifs(char *ifs, char c)
{
	static char *wspace = " \n\t";

	if (!(ft_cisin(ifs, c)))
		return (0);
	if ((ft_cisin(wspace, c)))
		return (IFS_WSPACE);
	return (IFS_REG);
}

int		insert_str(t_str *word, int *index, char *to_insert)
{
	char *save;

	while ((word->len + ft_strlen(to_insert)) >= word->size)
	{
		if (ft_str_realloc(word, INPUTSZ) == MEMERR)
			return (MEMERR);
	}
	if (!(save = ft_strdup(&(word->str[*index]))))
		return (MEMERR);
	ft_memcpy(&(word->str[*index]), to_insert, ft_strlen(to_insert));
	*index = ft_strlen(to_insert) + *index;
	ft_strcpy(&(word->str[*index]), save);
	word->len = ft_strlen(word->str);
	free(save);
	return (0);
}

char	*ft_next_field(char *value, char *ifs)
{
	int		i;
	char	*new_field;

	i = 0;
	while ((value[i]) && (!ft_is_ifs(ifs, value[i])))
		i++;
	if (!(new_field = ft_strndup(value, i)))
		return (NULL);
	while (ft_is_ifs(ifs, value[i]) == IFS_WSPACE)
		i++;
	if (ft_is_ifs(ifs, value[i]) == IFS_REG)
		i++;
	ft_memmove(value, value + i, ft_strlen(value + i));
	value[ft_strlen(value + i)] = 0;
	return (new_field);
}

int		next_squote(char *str, int index)
{
	index++;
	while ((str[index] != 0) && (str[index] != '\''))
		index++;
	return (index);
}

int		next_dquote(char *str, int index)
{
	index++;
	while (str[index] != 0)
	{
		if ((str[index] == '"') && (str[index - 1] != '\\'))
			break ;
		index++;
	}
	return (index);
}
