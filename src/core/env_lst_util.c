/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 21:55:47 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/15 18:37:36 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

t_environ	*new_env_node(char *name, char *value)
{
	t_environ *new;

	if ((name == NULL) || (value == NULL))
		return (NULL);
	new = ft_memalloc(sizeof(t_environ));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->value = value;
	new->to_export = 1;
	return (new);
}

t_environ	*env_to_lst(char *env_var)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while ((env_var[i]) && (env_var[i] != '='))
		i++;
	name = ft_strnew(i);
	if (name == NULL)
		return (NULL);
	ft_strncpy(name, env_var, i);
	if (env_var[i] != 0)
		i++;
	value = ft_strdup(&env_var[i]);
	if (value == NULL)
		return (NULL);
	return (new_env_node(name, value));
}
/*this was modified because get_env_value is broken
*/
t_environ	*get_env_node(char *name)
{
	size_t		len;
	t_environ	*tmp;

	len = 0;
	while (valid_env_char(name[len]))
		len++;
	if (len == 0)
		return (NULL);
	tmp = *g_environ;
	while (tmp != NULL)
	{
		if ((!ft_strncmp(tmp->name, name, len))
				&& (ft_strlen(tmp->name) == len))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void		add_node(t_environ **head, t_environ *to_add)
{
	t_environ *tmp;

	if (*head == NULL)
		*head = to_add;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = to_add;
		to_add->previous = tmp;
	}
}


int			env_tab_to_lst(char **env, t_environ **env_lst)
{
	int			i;
	t_environ	*tmp;

	i = 0;
	while (env[i] != NULL)
	{
		tmp = env_to_lst(env[i]);
		if (tmp == NULL)
			return (MEMERR);
		tmp->to_export = 1;
		add_node(env_lst, tmp);
		i++;
	}
	if (i == 0)
		*env = NULL;
	return (0);
}
