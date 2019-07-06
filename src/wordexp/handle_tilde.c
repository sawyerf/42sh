/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:52:28 by tduval            #+#    #+#             */
/*   Updated: 2019/07/06 18:53:12 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

int		expand_tilde_assign(t_str *word, int index)
{
	if ((word->str[index] == '~') && (tilde_valid(word->str[index + 1])))
		expand_tilde(word, &index, 1);
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
		return (expand_tilde(&(word->data), &index, 1));
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
