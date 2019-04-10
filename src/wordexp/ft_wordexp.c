/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordexp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/10 17:50:03 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

static void	heredoc_quote_rm(t_token *word)
{
	int index;

	index = 0;
	while (word->data.str[index])
	{
		if ((word->data.str[index] == '\\')
			&& (ft_cisin("$\n\\", word->data.str[index + 1])))
			shift_bslash(&(word->data), &index);
		else
			index++;
	}
}

int			ft_wordexp_heredoc(t_token *word)
{
	if (handle_tilde(word) == MEMERR)
		return (MEMERR);
	if (handle_exp_param(word, FT_TRUE) == MEMERR)
		return (MEMERR);
	heredoc_quote_rm(word);
	return (0);
}

int			ft_wordexp(t_token *word, t_bool is_redir)
{
	if (handle_tilde(word) == MEMERR)
		return (MEMERR);
	if (handle_exp_param(word, is_redir) == MEMERR)
		return (MEMERR);
	if (quote_removal(word) == MEMERR)
		return (MEMERR);
	return (0);
}
