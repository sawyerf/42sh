/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_if_null.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:50:51 by tduval            #+#    #+#             */
/*   Updated: 2019/07/06 18:50:52 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

char			*assign_sub_var(char *var_name, char *zone)
{
	char	*result;

	result = ft_strsub(zone, 1, ft_strlen(zone) - 2);
	envaddstr(&g_sh.local, var_name, result);
	return (result);
}

char			*substitute_by_len(char *cursor)
{
	char	*var_name;
	char	*env_value;
	char	*result;

	cursor++;
	result = NULL;
	var_name = get_var_exp(cursor);
	env_value = ft_strdup(get_env_value(var_name));
	log_info("--------------> substitute_by_len");
	if (ft_strequ(var_name, "#"))
		result = ft_itoa(1);
	else
		result = ft_itoa(ft_strlen(env_value));
	if (var_name)
		ft_strdel(&var_name);
	if (env_value)
		ft_strdel(&env_value);
	return (result);
}

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
