/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <ktlili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/05/08 15:40:54 by juhallyn         ###   ########.fr       */
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
	log_fatal("quoted str [%p]", str);
	if (str && str[0])
	{
		log_fatal("IS free");
		free(str);
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
	log_warn("var_name = %s", var_name);
	return (var_name);
}

char			*get_var_exp(char *cursor)
{
	log_warn("get_var_exp  CURSOR == [%s]", cursor);
	char	*var;
	char	*tmp;
	int		len;

	len = 0;
	var = NULL;
	tmp = cursor;
	while (*tmp && *tmp != ':' && *tmp != '}')
	{
		len++;
		tmp++;
	}
	var = ft_strndup(cursor, len);
	log_warn("get_var_exp == [%s]", var);
	log_fatal("ptr addr [%p]", var);
	return (var);
}

// ${parameter:-word}
char			*substitute_word_if_null(char *cursor, char *zone)
{
	log_warn("------------------ substitute_word_if_null -------------------");
	char	*var_name;
	char	*env_value;

	cursor++;
	var_name = NULL;
	env_value = NULL;
	var_name = get_var_exp(cursor);
	log_fatal("var_name ptr addr [%p]", var_name);
	env_value = ft_strdup(get_env_value(var_name));
	if (!env_value)
		env_value = check_second_exp_var(zone);
	if (var_name)
	{
		log_fatal("var_name ptr addr [%p]", var_name);
		ft_strdel(&var_name);
	}
	return (env_value);
}

char			*classic_sub(char *cursor)
{
	log_warn("------------------ classic_sub -------------------");
	char		*env_var;
	char		*env_value;
	const char	*empty_str = "";

	cursor++;
	empty_str = NULL;
	env_var = NULL;
	env_value = NULL;
	env_var = get_var_exp(cursor);
	if (env_var)
	{
		env_value = ft_strdup(get_env_value(env_var));
		log_fatal("var_name ptr addr [%p]", env_var);
		log_warn("classic_sub ret : [%s]", env_value);
		ft_strdel(&env_var);
		if (env_value && *env_value)
			return (env_value);
	}
	return ((char*)empty_str);
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
			return (result);
		}
		tmp++;
	}
	return (classic_sub(cursor));
}

char			*build_param(char *cursor)
{
	log_warn("---------------- build_param -------------");
	const char	*empty_str = "";
	char		*value;
	bool		str_free;

	value = NULL;
	str_free = false;
	if (*(cursor + 1) == '{')
		cursor++;
	else
		return (NULL);
	if (!value)
	{
		value = exp_sup(cursor);
		if (!value)
			value = (char*)empty_str;
	}
	if (!(value = quote_str(value)))
		return (NULL);
	log_warn("result build_param = [%s]", value);
	
	return (value);
}

int				expand_param(t_token **word, char **cursor,
				char *value, t_bool is_redir)
{
	log_warn("--------- expand param --------- [%s]  ", value);
	char				*ifs;
	int					i;

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
