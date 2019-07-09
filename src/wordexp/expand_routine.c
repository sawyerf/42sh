/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 13:47:13 by juhallyn          #+#    #+#             */
/*   Updated: 2019/07/09 14:00:41 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

void		quote_removal_tk(t_str *s)
{
	t_token t;

	ft_bzero(&t, sizeof(t_token));
	ft_memcpy(&t.data, s, sizeof(t_str));
	quote_removal(&t);
}

char		*expand_str_routine(char *cursor, int inside_dquote, t_str result,\
			char *value)
{
	while (*cursor)
	{
		if (*cursor == '"')
			inside_dquote = -inside_dquote;
		if (is_expandable(cursor, inside_dquote))
		{
			value = classic_sub(cursor);
			if (expand_classic(&result, &cursor, value) == MEMERR)
				return (NULL);
			ft_strdel(&value);
			continue;
		}
		else if ((*cursor == '\'') && (inside_dquote == 1))
			cursor = c_next_squote(cursor);
		else if (*cursor == '\\')
			cursor = c_next_bslash(cursor);
		cursor++;
	}
	quote_removal_tk(&result);
	return (result.str);
}
