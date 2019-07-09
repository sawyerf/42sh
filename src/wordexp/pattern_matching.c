/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:35:56 by tduval            #+#    #+#             */
/*   Updated: 2019/07/09 12:02:16 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"
#include "ft_patmatch.h"

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

char			*rev_pattern_matching(char *cursor, char *zone, int mode)
{
	log_warn("------------ rev_pattern_matching ---------------------\n");
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
	if (*cursor == '%')
		sub_error(cursor, BAD_SUB);
	if (mode)
		status = lsearch_rev_str(env_value, cmp, &nb_del);
	else
		status = bsearch_rev_str(env_value, (cmp + 1), &nb_del);
	if (status)
		env_value[ft_strlen(env_value) - nb_del] = '\0';
	log_warn("cmp : [%s] | env_value [%s] | status [%d]",
			cmp, env_value, status);
	ft_strdel(&cmp);
	ft_strdel(&var_name);
	return (env_value);
}

char			*pattern_matching(char *cursor, char *zone, int mode)
{
	char	*var_name;
	char	*env_value;
	char	*cmp;
	int		nb_del;
	bool	status;

	cursor++;
	status = false;
	var_name = get_var_exp(cursor);
	cmp = check_second_exp_var(zone);
	log_warn("------------ pattern_matching ---------------------\n");
	env_value = ft_strdup(get_env_value(var_name));
	if (mode)
		status = lsearch_str(env_value, cmp, &nb_del);
	else
		status = bsearch_str(env_value, (cmp + 1), &nb_del);
	if (status)
		ft_strcpy(env_value, env_value + nb_del);
	log_warn("cmp : [%s] | env_value [%s] | status [%d]", cmp,
			env_value, status);
	ft_strdel(&cmp);
	ft_strdel(&var_name);
	return (env_value);
}
