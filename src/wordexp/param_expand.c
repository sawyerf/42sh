/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <ktlili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/06/04 14:29:14 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

void		print_array(char **array)
{
	log_info("print array");
	int i = 0;
	while (array[i])
	{
		log_info("%s", array[i]);
		i++;
	}
}

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
	if (str && str[0])
		free(str);
	return (quoted);
}
// ${parameter:-word}
char			*check_second_exp_var(char *zone)
{
	log_warn("-----------  check_second_exp_var : [%s] ------------  ", zone);
	char	*var_name;

	var_name = NULL;
	var_name = ft_strsub(zone, 1, (ft_strlen(zone) - 2));
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
	while (*tmp && *tmp != ':' && *tmp != '}')
	{
		len++;
		tmp++;
	}
	var = ft_strndup(cursor, len);
	return (var);
}

char			*assign_sub_var(char *var_name, char *zone)
{
	log_fatal("var_name = [%s]", var_name);
	char	*result;

	result = ft_strsub(zone, 1, ft_strlen(zone) - 2);
	log_fatal("assign data [%s]", result);
	g_sh.env = envaddstr(g_sh.env, var_name, result);
	return (result);
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
	env_value = ft_strdup(get_env_value(var_name));
	log_warn("var_name [%s] | env_value [%s]", var_name, env_value);
	if (!env_value)
		env_value = check_second_exp_var(zone);
	if (var_name)
		ft_strdel(&var_name);
	return (env_value);
}

// ${parameter:=word}
char			*assign_word_if_null(char *cursor, char *zone)
{
	log_warn("------------------ assign_word_if_null -------------------");

	char	*var_name;
	char	*env_value;

	cursor++;
	var_name = NULL;
	var_name = get_var_exp(cursor);
	env_value = ft_strdup(get_env_value(var_name));

	log_warn("var_name [%s] | env_value [%s]", var_name, env_value);

	if (!env_value)
	{
		env_value = assign_sub_var(var_name, zone);
		zone = NULL;
	}
	if (var_name)
		ft_strdel(&var_name);

	log_fatal("ENV VALUE {%s}", env_value);
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
		ft_strdel(&env_var);
		if (env_value && *env_value)
			return (env_value);
	}
	return ((char*)empty_str);
}

char			*exp_sup(char *cursor, bool classic_substitute)
{
	char	previous_char;
	char	*tmp;
	char	*result;

	if (classic_substitute)
		return (classic_sub(cursor));
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
		if (previous_char == ':' && (*tmp) == '=')
		{
			result = assign_word_if_null(cursor, tmp);
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
		log_fatal("exp_sup VALUE = [%s]", value);
		if (!value)
			value = (char*)empty_str;
	}
	if (!(value = quote_str(value)))
		return (NULL);
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
	log_warn("Word-exp : [%s]\n", word->data.str);
	return (0);
}
