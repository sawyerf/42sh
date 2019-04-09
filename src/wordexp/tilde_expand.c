/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/09 21:39:01 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

int		tilde_valid(char c)
{
	if ((c == 0) || (c == '/') || (c == ':'))
		return (1);
	return (0);
}

char	*quote_home(char *str)
{
	char *new;

	new = ft_strnew(ft_strlen(str) + 2);
	if (!new)
		return (NULL);
	new[0] = '\'';
	ft_strcpy(new + 1, str);
	new[ft_strlen(new)] = '\'';
	return (new);
}

int		expand_tilde(t_str *word, int *index, int add_quote)
{
	char *home;

	ft_memmove(word->str + *index, word->str + *index + 1, word->len - *index);
	word->len = word->len - 1;
	word->str[word->len] = '\0';
	home = get_env_value("HOME");
	if ((!home) || (*home == '\0'))
		return (0);
	if ((add_quote) && (!(home = quote_home(home))))
		return (MEMERR);
	if (insert_str(word, index, home) == MEMERR)
		return (MEMERR);
	if (add_quote)
		free(home);
	return (0);
}

int		expand_tilde_assign(t_str *word, int index)
{
	if ((word->str[index] == '~') && (tilde_valid(word->str[index + 1])))
	{
		expand_tilde(word, &index, 1);
	}
	while (word->str[index])
	{
		if ((word->str[index] == ':') && (word->str[index + 1] == '~'))
		{
			index++;
			if (expand_tilde(word, &index, 1) == MEMERR)
				return (MEMERR);
			continue;
		}
		if (word->str[index] == '\'')
			index = next_squote(word->str, index);
		else if ((word->str[index] == '\\') && (word->str[index + 1] != 0))
			index = index + 1;
		else if (word->str[index] == '\'')
			index = next_dquote(word->str, index);
		index++;
	}
	return (0);
}

int		handle_tilde(t_token *word)
{
	int index;

	index = 0;
	if ((word->data.str[0] == '~') && (tilde_valid(word->data.str[1])))
	{
		return (expand_tilde(&(word->data), &index, 1));
	}
	if (word->type == ASSIGN)
	{
		while (word->data.str[index])
		{
			if (word->data.str[index] == '=')
				break ;
			index++;
		}
		return (expand_tilde_assign(&(word->data), index + 1));
	}
	return (0);
}
