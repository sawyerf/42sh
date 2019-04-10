/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 19:33:29 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/10 18:28:49 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

void	shift_str_left(t_str *str_w, int index)
{
	ft_memmove(str_w->str + index, str_w->str + index + 1, str_w->len - index);
	str_w->len = str_w->len - 1;
}

void	shift_bslash(t_str *str_w, int *index)
{
	shift_str_left(str_w, *index);
	if (str_w->str[*index] == '\n')
		shift_str_left(str_w, *index);
	if (str_w->str[*index])
		*index = *index + 1;
}

void	inside_dquote_qr(t_str *str_w, int *index)
{
	if (str_w->str[*index] == '"')
		shift_str_left(str_w, *index);
	while (str_w->str[*index])
	{
		if (str_w->str[*index] == '"')
		{
			shift_str_left(str_w, *index);
			break ;
		}
		else if ((str_w->str[*index] == '\\')
			&& (ft_cisin("$\n\"\\", str_w->str[*index + 1])))
			shift_bslash(str_w, index);
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
			shift_bslash(&(word->data), &index);
		else
			index++;
	}
	return (0);
}
