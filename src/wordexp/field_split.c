/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 12:46:44 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/04 21:40:44 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

int		is_ifs(char c, char *ifs)
{
	while (*ifs)
	{
		if (*ifs == c)
			return (1);
		ifs++;
	}
	return (0);
}

int		split_candidate(char *str, char *ifs)
{
	int index;

	index = 0;
	while (str[index])
	{
		if (is_ifs(str[index], ifs))
			return (1);
		index++;
	}
	return (0);
}

void	trim_str(t_str *str_w, char *ifs)
{
	int	index;

	index = 0;
	while (is_ifs(str_w->str[index], ifs))
		index++;
	ft_memmove(str_w->str, str_w->str + index, ft_strlen(str_w->str) - index);
	str_w->len = str_w->len - index;
	str_w->str[str_w->len] = '\0';
}

void	ft_trim_ifs(t_str *str_w, char *ifs)
{
	trim_str(str_w, ifs);
	ft_strrev(str_w->str);
	trim_str(str_w, ifs);
	ft_strrev(str_w->str);
}

int		extract_field(t_str *str_w, int *index, t_token **head, char *ifs)
{
	int		end;
	t_token	*new;

	end = *index;
	while (str_w->str[end])
	{
		if (is_ifs(str_w->str[end], ifs))
			break ;
		if (str_w->str[end] == '\'')
			end = next_squote(str_w->str, end) + 1;
		else if (str_w->str[end] == '"')
			end = next_dquote(str_w->str, end) + 1;
		else if (str_w->str[end] == '\\')
			end = next_bslash(str_w->str, end) + 1;
		else
			end++;
	}
	if ((!(new = new_token(0))) || (str_putnstr(str_w->str + *index,
			&(new->data), end - *index) == MEMERR))
		return (MEMERR);
	add_token(head, new);
	*index = end;
	return (0);
}

void	replace_token(t_token *word, t_token *new_fields)
{
	t_token	*save;

	save = word->next;
	if (word->data.str)
		free(word->data.str);
	ft_memcpy(word, new_fields, sizeof(t_token));
	while (word->next)
		word = word->next;
	word->next = save;
	free(new_fields);
}

int		handle_ifs(t_token *word, char *ifs)
{
	int		index;
	t_token	*new_fields;

	ft_trim_ifs(&(word->data), ifs);
	if (!split_candidate(word->data.str, ifs))
		return (0);
	index = 0;
	new_fields = NULL;
	while (word->data.str[index])
	{
		while (is_ifs(word->data.str[index], ifs))
			index++;
		if (extract_field(&(word->data), &index, &new_fields, ifs) == MEMERR)
			return (MEMERR);
	}
	replace_token(word, new_fields);
	return (0);
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

int		handle_field_split(t_token *word)
{
	static char	*default_ifs = " \t\n";
	char		*ifs;

	if (!(ifs = get_env_value("IFS")))
		ifs = default_ifs;
	else
	{
		if (!(ifs = expand_ifs(ifs)))
			return (MEMERR);
		if (*ifs == 0)
		{
			free(ifs);
			ifs = default_ifs;
		}
	}
	if ((*ifs == '\0') || (!split_candidate(word->data.str, ifs)))
		return (0);
	if (handle_ifs(word, ifs) == MEMERR)
		return (MEMERR);
	return (0);
}
