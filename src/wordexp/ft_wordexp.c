/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordexp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/02 20:00:58 by ktlili           ###   ########.fr       */
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

static int extract_fields(t_token *word, char **fields)
{
	t_token *tmp;
	t_token *head;

	head = NULL;
	while (*fields)
	{
		if (!(tmp = new_token(0)))
			return (MEMERR);
		free(tmp->data.str);
		tmp->data.str = *fields;
		tmp->data.len = ft_strlen(*fields);
		tmp->data.size = tmp->data.len + 1;
		add_token(&head, tmp);
		fields++;
	}
	tmp->next = word->next;
	word->next = head;
	return (0);
}

int			quote_fields(char **fields)
{
	int i;
	char *tmp;

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

int			filename_expansion(t_token *word, t_bool is_redir)
{
	char **fields;
	t_token *tmp;
	t_token *head;

	if (is_redir)
		return (0);
	if (!(fields = ret_matches(word->data.str)))
		return (MEMERR);
	if (ft_strequ(word->data.str, *fields))
	{
		free_tab(fields);
		return (0);
	}
	if (quote_fields(fields) == MEMERR)
		return (MEMERR);
	free(word->data.str);
	word->data.str = *fields;
	word->data.len = ft_strlen(*fields);
	if ((*(fields + 1)))
	{
		if (extract_fields(word, fields + 1) == MEMERR)
			return (MEMERR);
	}
	free(fields);
	return (0);
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
/*	this is broken because the function final_step removes backslashes, wich is quote_removal's job.
 */
	if (filename_expansion(word, is_redir) == MEMERR)
		return (MEMERR);
	if (quote_removal(word) == MEMERR)
		return (MEMERR);
	return (0);
}
