/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordexp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <ktlili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/09 11:59:05 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"
#include "ft_patmatch.h"

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

int			quote_fields(char **fields)
{
	char	*tmp;
	int		i;

	i = 0;
	while (fields[i])
	{
		if (!(tmp = quote_str(fields[i])))
			return (MEMERR);
		free(fields[i]);
		fields[i] = tmp;
		i++;
	}
	return (0);
}

void		sub_error(char *cursor, int err)
{
	if (err == BAD_SUB)
		ft_dprintf(2, "{%s : bad substitution", cursor);
	g_sh.status = 1;
}

int			ft_wordexp(t_token *word, t_bool is_redir)
{
	t_token *save;

	log_info("------------  ft_wordexp -------------------------");
	log_info("Word : [%s]", word->data.str);
	if (handle_tilde(word) == MEMERR)
		return (MEMERR);
	save = word->next;
	if (handle_exp_param(word, is_redir) == MEMERR)
		return (MEMERR);
	if (filename_expansion(word, is_redir) == MEMERR)
		return (MEMERR);
	if (quote_removal(word) == MEMERR)
		return (MEMERR);
	return (0);
}
