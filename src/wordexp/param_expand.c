/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <ktlili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/05/03 22:09:49 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

static size_t	quote_str_len(char *str)
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

static char		*quote_str(char *str)
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

// ${parameter:-word}
char			*check_second_exp_var(char *zone)
{
	log_warn("-----------  check_second_exp_var : [%s] ------------  ", zone);
	char	*var_name;

	var_name = NULL;
	var_name = ft_strsub(zone, 1, (ft_strlen(zone) - 2));
	log_warn(
		"var_name = %s", var_name
	);
	if (var_name)
		return (var_name);
	return (var_name);
}

char			*get_var_exp(char *cursor)
{
	char	*var;
	char	*tmp;
	int		len;

	len = 0;
	var = NULL;
	tmp = cursor;
	while (*tmp && *tmp != ':')
	{
		len++;
		tmp++;
	}
	var = ft_strndup(cursor, len);
	log_warn("get_var_exp == [%s]", var);
	return (var);
}

// ${parameter:-word}
char			*substitute_word_if_null(char *cursor, char *zone)
{
	log_warn("------------------ substitute_word_if_null -------------------");
	char	*env_var;
	char	*env_value;

	cursor++;
	env_var = NULL;
	env_value = NULL;
	env_var = get_var_exp(cursor);
	env_value = get_env_value(env_var);
	if (!env_value)
	{
		log_fatal("no value for [%s]\n\n", env_var);
		env_value = check_second_exp_var(zone);
		log_warn(" |!| second env value = [%s]\n", env_value);
	}
	else
		log_fatal("resut value for [%s] is [%s]\n", env_var, env_value);
	log_info("CURSOR = [%s]\nzone = [%s]", cursor, zone);
	ft_strdel(&env_var);
	return (env_value);
}

char			*exp_sup(char *cursor)
{
	char	previous_char;
	char	*tmp;
	char	*result;

	result = NULL;
	previous_char = '\0';
	tmp = cursor;
	tmp++;
	while (*tmp)
	{
		previous_char = *(tmp - 1);
		if (previous_char == ':' && (*tmp) == '-')
		{
			result = substitute_word_if_null(cursor, tmp);
			log_warn("RESULT = [%s]", result);
			return (result);
		}
		tmp++;
	}
	return (result);
}

char			*build_param(char *cursor)
{
	static char	*empty_str = "";
	char		*value;

	value = NULL;
	if (*(cursor + 1) == '{')
	{
		cursor++;
		// value = exp_sup(cursor);
		log_warn("result -- = [%s]", value);
		// log_info("--------------- BUILD PARAM -------------------------");
		// log_warn("cursor : [%s]", cursor);
	}
	if (!value)
	{
		log_warn("!value : get_env_value");
		// value = get_env_value(cursor + 1);
		value = exp_sup(cursor);
	}
	if (!value)
	{
		log_warn("!value : empty_str");
		value = empty_str;
	}
	if (!(value = quote_str(value)))
		return (NULL);
	log_warn("value	= [%s]", value);
	return (value);
}

int				expand_param(t_token **word, char **cursor,
					char *value, t_bool is_redir)
{
	char				*ifs;
	int					i;

	log_warn("--------- expand param --------- [%s]  ", value);
	is_redir = FT_TRUE;
	if (get_ifs(&ifs) == MEMERR)
		return (MEMERR);
	delete_varname(*cursor);
	if ((!ifs) || (is_redir == FT_TRUE) || (!split_candidate(value, ifs)))
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

	cursor = NULL;
	cursor = word->data.str;
	inside_dquote = 1;
	while (*cursor)
	{
		if (*cursor == '"')
			inside_dquote = -inside_dquote;
		if ((*cursor == '$') && (*(cursor + 1) != 0))
		{
			if ((!(value = build_param(cursor))
			|| (expand_param(&word, &cursor, value, is_redir) == MEMERR)))
				return (MEMERR);
			// word->data.str = ft_strdup(value);
			ft_strdel(&value);
			continue;
		}
		else if ((*cursor == '\'') && (inside_dquote == 1))
			cursor = c_next_squote(cursor);
		else if (*cursor == '\\')
			cursor = c_next_bslash(cursor);
		cursor++;
	}
	log_warn("Word-exp : [%s]", word->data.str);
	return (0);
}
