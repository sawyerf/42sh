/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 22:16:00 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/15 18:37:34 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

char	*get_value(char *env_var)
{
	int i;

	i = 0;
	while (valid_env_char(env_var[i]))
		i++;
	if (env_var[i] == 0)
		return (env_var + i);
	return (env_var + i + 1);
}

char	*construct_env_var(const char *name, const char *value)
{
	size_t		tot_len;
	size_t		len_name;
	char		*new;

	len_name = ft_strlen(name);
	tot_len = len_name + ft_strlen(value) + 1;
	new = ft_strnew(tot_len);
	if (new == NULL)
		return (NULL);
	ft_strcpy(new, name);
	new[len_name] = '=';
	ft_strcpy(new + len_name + 1, value);
	return (new);
}

void	delete_env_node(t_environ *to_del)
{
	if (to_del->previous != NULL)
		to_del->previous->next = to_del->next;
	else
		*g_environ = to_del->next;
	if (to_del->next != NULL)
		to_del->next->previous = to_del->previous;
	free(to_del->name);
	if (to_del->value != NULL)
		free(to_del->value);
	free(to_del);
}

int		lst_len(t_environ *const env_lst)
{
	int			len;
	t_environ	*tmp;

	len = 0;
	tmp = env_lst;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

char	**lst_to_tab(t_environ *const env_lst, int size)
{
	int			len;
	t_environ	*tmp;
	char		**machintruc;

	len = lst_len(env_lst);
	machintruc = ft_memalloc((len + size + 1) * sizeof(char*));
	if (machintruc == NULL)
		return (NULL);
	len = 0;
	tmp = env_lst;
	while (tmp != NULL)
	{
		if (tmp->to_export)
		{
			machintruc[len] = construct_env_var(tmp->name, tmp->value);
			if (machintruc[len] == NULL)
			{
				free_tab(machintruc);
				return (NULL);
			}
		len++;
		}
		tmp = tmp->next;
	}
	machintruc[len] = NULL;
	return (machintruc);
}
