/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsearch_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:42:18 by tduval            #+#    #+#             */
/*   Updated: 2019/07/06 18:58:03 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_patmatch.h"
#include "ft_wordexp.h"

char		*assign_word_if_null(char *cursor, char *zone)
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

char		*classic_sub(char *cursor)
{
	char		*env_var;
	char		*env_value;

	cursor++;
	env_var = NULL;
	env_value = NULL;
	env_var = get_var_exp(cursor);
	log_warn("-------------------- classic_sub -------------------");
	if (env_var)
	{
		env_value = dget_env_value(env_var);
		ft_strdel(&env_var);
		if (env_value)
			return (env_value);
	}
	return (ft_strdup(""));
}

char		*test_parameter(char *cursor, char *zone)
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
			ft_dprintf(2, "42sh: %s: paramètre vide ou non défini", var_name);
		else
			ft_dprintf(2, "42sh: %s: %s", var_name, error_msg);
		g_sh.status = 1;
	}
	if (var_name)
		ft_strdel(&var_name);
	if (error_msg)
		ft_strdel(&error_msg);
	return (env_value);
}

char		*sub_word_if_not_null(char *cursor, char *zone)
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

bool		lsearch_str(char *str, char *search, int *nb_del)
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
			log_info("str [%s] | search [%s] | nb_del [%d]",
					str, search, *nb_del);
			return (true);
		}
		str[i] = c;
		i++;
	}
	*nb_del = 0;
	log_info("str [%s] | search [%s] | nb_del [%d]", str, search, *nb_del);
	return (false);
}
