/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 22:17:22 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/06 16:07:09 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

int		valid_env_char(char c)
{
	if ((ft_isalnum(c)) || (c == '_'))
		return (1);
	return (0);
}

int		valid_env_name(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (!valid_env_char(str[i]))
			return (0);
		i++;
	}
	if (i != ft_strlen(str))
		return (0);
	return (1);
}

char	*tab_get_value(char *name, char **env)
{
	int i;
	int len;

	if ((name == NULL) || (env == NULL))
		return (NULL);
	i = 0;
	len = ft_strlen(name);
	while (env[i] != NULL)
	{
		if ((!ft_strncmp(name, env[i], len)) && (env[i][len] == '='))
			return (get_value(env[i]));
		i++;
	}
	return (NULL);
}
/*
	this is broken, we mix NULL memerror with NULL no var found
char	*get_env_value(char *name)
{
	t_environ	*tmp;
	char		*clean_name;
	int			i;

	i = 0;
	while (valid_env_char(name[i]))
		i++;
	clean_name = ft_strnew(i);
	if (clean_name == NULL)
		return (NULL);
	ft_strncpy(clean_name, name, i);
	tmp = get_env_node(clean_name);
	free(clean_name);
	if (tmp != NULL)
		return (tmp->value);
	return (NULL);
}

*/
char	*get_env_value(char *name)
{
	t_environ	*tmp;

	tmp = get_env_node(name);
	if (tmp != NULL)
		return (tmp->value);
	return (NULL);
}

int		set_shell_env(char *name, char *newvalue, int to_export)
{
	t_environ *tmp;

	if (newvalue == NULL)
		newvalue = "";
	if ((tmp = get_env_node(name)) == NULL)
	{
		tmp = new_env_node(ft_strdup(name), ft_strdup(newvalue));
		if (tmp != NULL)
			add_node(g_environ, tmp);
		else
			return (MEMERR);
		tmp->to_export = to_export;
	}
	else
	{
		if (tmp->value != NULL)
			free(tmp->value);
		tmp->value = ft_strdup(newvalue);
		if (tmp->value == NULL)
			return (MEMERR);
		tmp->to_export = to_export;
	}
	return (0);
}

