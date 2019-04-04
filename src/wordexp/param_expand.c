/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/04 22:08:14 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

static	size_t	quote_str_len(char *str)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '\'') || (str[i] == '"') || (str[i] == '\\'))
			count++;
		i++;
	}
	return (count);
}

char	*quote_str(char *str)
{
	size_t	count;
	int		j;
	int		i;
	char	*quoted;

	count = quote_str_len(str);
	i = ft_strlen(str);
	if (!(quoted = ft_strnew(i + count)))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'') || (str[i] == '"') || (str[i] == '\\'))
		{
			quoted[j] = '\\';
			j++;
		}
		quoted[j] = str[i];
		i++;
		j++;
	}
	return (quoted);
}

int		expand_param(t_str *str_w, int *index, char *to_insert)
{
	int		trunc;
	int		i;

	i = *index + 1;
	trunc = 1;
	if (str_w->str[i] == '{')
	{
		i++;
		trunc = 3;
	}
	while (parser_is_name_c(str_w->str[i]))
	{
		trunc++;
		i++;
	}
	ft_memmove(str_w->str + *index, str_w->str + *index + trunc,
			str_w->len - *index - trunc);
	str_w->len = str_w->len - trunc;
	str_w->str[str_w->len] = '\0';
	if (insert_str(str_w, index, to_insert) == MEMERR)
		return (MEMERR);
	return (0);
}

char	*build_param(t_str *str_w, int index)
{
	static char	*empty_str = "";
	char		*value;

	if (str_w->str[index] == '{')
		index++;
	value = get_env_value(str_w->str + index);
	if (!value)
		value = empty_str;
	if (!(value = quote_str(value)))
		return (NULL);
	return (value);
}

int		handle_exp_param(t_token *word)
{
	int		index;
	char	*value;
	int		inside_dquote;

	index = 0;
	inside_dquote = 1;
	while (word->data.str[index])
	{
		if (word->data.str[index] == '"')
			inside_dquote = -inside_dquote;
		if ((word->data.str[index] == '$') && (word->data.str[index + 1] != 0))
		{
			if ((!(value = build_param(&(word->data), index + 1)))
			|| (expand_param(&(word->data), &index, value) == MEMERR))
				return (MEMERR);
			free(value);
			continue;
		}
		else if ((word->data.str[index] == '\'') && (inside_dquote == 1))
			index = next_squote(word->data.str, index);
		else if (word->data.str[index] == '\\')
			index = next_bslash(word->data.str, index);
		index++;
	}
	return (0);
}
