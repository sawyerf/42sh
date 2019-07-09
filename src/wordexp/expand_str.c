/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:52:36 by juhallyn          #+#    #+#             */
/*   Updated: 2019/07/09 14:02:03 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

int		expand_classic(t_str *s, char **cursor, char *value)
{
	int		i;
	int		dummy;

	delete_varname(*cursor);
	i = *cursor - s->str;
	dummy = i;
	if (insert_str(s, &dummy, value) == MEMERR)
		return (MEMERR);
	*cursor = s->str + i + ft_strlen(value);
	return (0);
}

int		init_t_str(t_str *s, char *tocpy)
{
	int i;

	i = 0;
	ft_bzero(s, sizeof(t_str));
	if (!(s->str = ft_memalloc(INPUTSZ * sizeof(char))))
		return (MEMERR);
	s->size = INPUTSZ;
	if (insert_str(s, &i, tocpy) == MEMERR)
		return (MEMERR);
	return (0);
}

int		is_expandable(char *cursor, int in_dquote)
{
	if ((*cursor == '$') && (*(cursor + 1) != 0)
		&& !((in_dquote == -1) && (*(cursor + 1) == '"')))
		return (1);
	return (0);
}

char	*expand_str(char *cursor)
{
	char	*value;
	t_str	result;
	int		inside_dquote;

	if (init_t_str(&result, cursor))
		return (NULL);
	value = NULL;
	cursor = result.str;
	inside_dquote = 1;
	return (expand_str_routine(cursor, inside_dquote, result, value));
}
