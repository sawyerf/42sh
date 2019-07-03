/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <ktlili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/03 13:40:15 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"
#include "ft_patmatch.h"

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
	char	*var_name;

	var_name = NULL;
	if (ft_strlen(zone) > 2)
		var_name = ft_strsub(zone, 1, ft_strchr(zone, '}') - zone - 1);
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
	while (*tmp && *tmp != ':' && *tmp != '}' && *tmp != '%')
	{
		len++;
		tmp++;
	}
	var = ft_strndup(cursor, len);
	return (var);
}

char			*assign_sub_var(char *var_name, char *zone)
{
	char	*result;

	result = ft_strsub(zone, 1, ft_strlen(zone) - 2);
	g_sh.local = envaddstr(g_sh.local, var_name, result);
	return (result);
}

// ${#parameter}
char			*substitute_by_len(char *cursor)
{
	char	*var_name;
	char	*env_value;
	char	*result;

	cursor++;
	result = NULL;
	var_name = get_var_exp(cursor);
	env_value = ft_strdup(get_env_value(var_name));
	result = ft_itoa(ft_strlen(env_value));
	if (var_name)
		ft_strdel(&var_name);
	if (env_value)
		ft_strdel(&env_value);
	return (result);
}

// ${parameter:-word}
char			*substitute_word_if_null(char *cursor, char *zone)
{
	char	*var_name;
	char	*env_value;

	cursor++;
	var_name = NULL;
	env_value = NULL;
	var_name = get_var_exp(cursor);
	env_value = ft_strdup(get_env_value(var_name));
	if (!env_value)
		env_value = check_second_exp_var(zone);
	if (var_name)
		ft_strdel(&var_name);
	return (env_value);
}

// ${parameter:=word}
char			*assign_word_if_null(char *cursor, char *zone)
{
	char	*var_name;
	char	*env_value;

	cursor++;
	var_name = NULL;
	var_name = get_var_exp(cursor);
	env_value = ft_strdup(get_env_value(var_name));
	if (!env_value)
	{
		env_value = assign_sub_var(var_name, zone);
		zone = NULL;
	}
	if (var_name)
		ft_strdel(&var_name);
	return (env_value);
}

char			*classic_sub(char *cursor)
{
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

// ${parameter:?msg_err}
char			*test_parameter(char *cursor, char *zone)
{
	char		*var_name;
	char		*env_value;
	char		*error_msg;

	cursor++;
	error_msg = NULL;
	var_name = NULL;
	var_name = get_var_exp(cursor);
	env_value = ft_strdup(get_env_value(var_name));
	error_msg = ft_strsub(zone, 1, ft_strlen(zone) - 2);
	if (!env_value)
	{
		if (!error_msg || ft_strlen(error_msg) == 0)
			ft_dprintf(2, "21sh: %s: paramètre vide ou non défini", var_name);
		else
			ft_dprintf(2, "21sh: %s: %s", var_name, error_msg);
		g_sh.status = 1;
	}
	if (var_name)
		ft_strdel(&var_name);
	if (error_msg)
		ft_strdel(&error_msg);
	return (env_value);
}

// ${parameter:+word}
char			*sub_word_if_not_null(char *cursor, char *zone)
{
	char	*var_name;
	char	*env_value;
	char	*word;

	cursor++;
	word = NULL;
	word = check_second_exp_var(zone);
	var_name = get_var_exp(cursor);
	env_value = ft_strdup(get_env_value(var_name));
	if (env_value)
	{
		ft_strdel(&env_value);
		ft_strdel(&var_name);
		return (word);
	}
	ft_strdel(&var_name);
	ft_strdel(&word);
	return (NULL);
}


bool			lsearch_str(char *str, char *search, int *nb_del)
{
	int		i;
	char	c;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		c = str[i];
		str[i] = 0;
		if (matches(str, search, 0))
		{
			str[i] = c;
			*nb_del = i;
			log_info("str [%s] | search [%s] | nb_del [%d]", str, search, *nb_del);
			return (true);
		}
		str[i] = c;
		i++;
	}
	*nb_del = 0;
	log_info("str [%s] | search [%s] | nb_del [%d]", str, search, *nb_del);
	return (false);
}

bool			bsearch_str(char *str, char *search, int *nb_del)
{
	int		i;
	char	c;

	log_info("str [%s] search [%s]", str, search);
	if (!str)
		return (false);
	i = ft_strlen(str);
	while (i >= 0)
	{
		c = str[i];
		str[i] = 0;
		if (matches(str, search, 0))
		{
			str[i] = c;
			*nb_del = i;
			return (true);
		}
		str[i] = c;
		i--;
	}
	*nb_del = 0;
	return (false);
}

bool			bsearch_rev_str(char *str, char *search, int *nb_del)
{
	int		i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (matches(str + i, search, 0))
		{
			*nb_del = ft_strlen(str) - i;
			return (true);
		}
		i++;
	}
	*nb_del = 0;
	return (false);
}

bool			lsearch_rev_str(char *str, char *search, int *nb_del)
{
	int		i;

	if (!str)
		return (false);
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (matches(str + i, search, 0))
		{
			*nb_del = ft_strlen(str) - i;
			return (true);
		}
		i--;
	}
	*nb_del = 0;
	return (false);
}

char 			*rev_pattern_matching(char *cursor, char *zone, int mode)
{
	log_warn("------------ pattern_matching ---------------------\n");
	char	*var_name;
	char	*env_value;
	char	*cmp;
	int		nb_del;
	bool	status;

	cursor++;
	status = false;
	var_name = get_var_exp(cursor);
	cmp = check_second_exp_var(zone);
	env_value = ft_strdup(get_env_value(var_name));
	if (mode)
		status = lsearch_rev_str(env_value, cmp, &nb_del);
	else
		status = bsearch_rev_str(env_value, (cmp + 1), &nb_del);
	if (status)
		env_value[ft_strlen(env_value) - nb_del] = '\0';
	log_warn("cmp : [%s] | env_value [%s] | status [%d]", cmp,env_value, status);
	ft_strdel(&cmp);
	ft_strdel(&var_name);
	return (env_value);
}

char 			*pattern_matching(char *cursor, char *zone, int mode)
{
	log_warn("------------ pattern_matching ---------------------\n");
	char	*var_name;
	char	*env_value;
	char	*cmp;
	int		nb_del;
	bool	status;

	cursor++;
	status = false;
	var_name = get_var_exp(cursor);
	cmp = check_second_exp_var(zone);
	env_value = ft_strdup(get_env_value(var_name));
	if (mode)
		status = lsearch_str(env_value, cmp, &nb_del);
	else
		status = bsearch_str(env_value, (cmp + 1), &nb_del);
	if (status)
		ft_strcpy(env_value, env_value + nb_del);
	log_warn("cmp : [%s] | env_value [%s] | status [%d]", cmp,env_value, status);
	ft_strdel(&cmp);
	ft_strdel(&var_name);
	return (env_value);
}


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
