/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 19:33:29 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/01 12:50:03 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

void	shift_str_left(t_str *str_w, int index)
{
	ft_memmove(str_w->str + index, str_w->str + index + 1, str_w->len - index);
	str_w->len = str_w->len - 1;
}

void	inside_dquote_qr(t_str *str_w, int *index)
{
	shift_str_left(str_w, *index);
	while (str_w->str[*index])
	{
		if (str_w->str[*index] == '"')
		{
			shift_str_left(str_w, *index);
			break ;
		}
		else if (str_w->str[*index] == '\\')
		{
			shift_str_left(str_w, *index);
			if (str_w->str[*index])
				// we should reject backslahs at endofline in lexer
				*index = *index + 1;
		}
		else
			*index = *index + 1;
	}
}

void	inside_squote_qr(t_str *str_w, int *index)
{
	shift_str_left(str_w, *index);
	while (str_w->str[*index])
	{
		if (str_w->str[*index] == '\'')
		{
			shift_str_left(str_w, *index);
			break ;
		}
		*index = *index + 1;
	}
}

int		quote_removal(t_token *word)
{
	int index;

	index = 0;
	while (word->data.str[index])
	{
		if (word->data.str[index] == '"')
			inside_dquote_qr(&(word->data), &index);
		else if (word->data.str[index] == '\'')
			inside_squote_qr(&(word->data), &index);
		else if (word->data.str[index] == '\\')
		{
			shift_str_left(&(word->data), index);
			if (word->data.str[index])
				// we should reject backslahs at endofline in lexer
				index = index + 1;
		}
		else
			index++;
	}
	return (0);
}
