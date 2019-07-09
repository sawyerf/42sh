/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exp_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 17:57:13 by tduval            #+#    #+#             */
/*   Updated: 2019/07/08 20:21:35 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"
#include "ft_patmatch.h"

char			*select_exp(char *cursor, char *tmp)
{
	char	previous_char;

	previous_char = '\0';
	while (*tmp)
	{
		previous_char = *(tmp - 1);
		if (previous_char == ':' && (*tmp) == '-')
			return (substitute_word_if_null(cursor, tmp));
		if (previous_char == ':' && (*tmp) == '=')
			return (assign_word_if_null(cursor, tmp));
		if (previous_char == ':' && (*tmp) == '?')
			return (test_parameter(cursor, tmp));
		if (previous_char == ':' && (*tmp) == '+')
			return (sub_word_if_not_null(cursor, tmp));
		if (ft_strncmp(tmp, "%%", 2) == 0)
			return (rev_pattern_matching(cursor, tmp, 0));
		else if ((*tmp) == '%')
			return (rev_pattern_matching(cursor, tmp, 1));
		if (ft_strncmp(tmp, "##", 2) == 0)
			return (pattern_matching(cursor, tmp, 0));
		else if ((*tmp) == '#')
			return (pattern_matching(cursor, tmp, 1));
		tmp++;
	}
	return (classic_sub(cursor));
}

char			*exp_sup(char *cursor, bool classic_substitute)
{
	char	previous_char;
	char	*tmp;
	char	*result;

	log_info("-------------->  exp_sup");
	if (classic_substitute)
		return (classic_sub(cursor));
	result = NULL;
	previous_char = '\0';
	tmp = cursor;
	tmp++;
	if (*tmp && *tmp == '#')
		return (substitute_by_len(tmp));
	return (select_exp(cursor, tmp));
}

char			*build_param(char *cursor)
{
	char		*value;
	char		*ret;
	bool		classic_substitute;

	value = NULL;
	classic_substitute = true;
	if (*(cursor + 1) == '{')
	{
		cursor++;
		classic_substitute = false;
	}
	if (!value)
	{
		value = exp_sup(cursor, classic_substitute);
		if (!value)
			value = ft_strdup("");
	}
	ret = quote_str(value);
	ft_strdel(&value);
	return (ret);
}

int				expand_param(t_token **word, char **cursor,
		char *value, t_bool is_redir)
{
	char				*ifs;
	int					i;

	if (get_ifs(&ifs) == MEMERR)
		return (MEMERR);
	delete_varname(*cursor);
	if ((!ifs) || ((*word)->type == ASSIGN)
			|| (is_redir == FT_TRUE) || (!split_candidate(value, ifs)))
	{
		i = *cursor - (*word)->data.str;
		if (c_insert_str(*word, *cursor, value) == MEMERR)
			return (MEMERR);
		*cursor = (*word)->data.str + i + ft_strlen(value);
		return (0);
	}
	return (handle_ifs(word, cursor, value, ifs));
}

int				handle_exp_param(t_token *word, t_bool is_redir)
{
	char	*cursor;
	char	*value;
	int		inside_dquote;

	cursor = word->data.str;
	inside_dquote = 1;
	while (*cursor)
	{
		if (*cursor == '"')
			inside_dquote = -inside_dquote;
			//should be is expandable
		if ((*cursor == '$') && (*(cursor + 1) != 0))
		{
			if ((!(value = build_param(cursor))
				|| (expand_param(&word, &cursor, value, is_redir) == MEMERR)))
				return (MEMERR);
			ft_strdel(&value);
			continue;
		}
		else if ((*cursor == '\'') && (inside_dquote == 1))
			cursor = c_next_squote(cursor);
		else if (*cursor == '\\')
			cursor = c_next_bslash(cursor);
		cursor++;
	}
	return (0);
}
