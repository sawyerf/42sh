/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   craft_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:22:06 by ktlili            #+#    #+#             */
/*   Updated: 2019/03/19 10:35:38 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"
/*
 * replace ft_ptr_arr_len with ft_tablen
 */
static int	ft_ptr_arr_len(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);

}

static char	**cpy_array(char **to, char **from)
{
	int i;

	i = 0;
	while (from[i])
	{
		to[i] = ft_strdup(from[i]);
		if (to[i] == NULL)
			return (NULL);
		i++;
	}
	return (to);
}

int	env_is_set(char *key, char **env)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while ((key[len]) && (key[len] != '='))
		len++;
	while (env[i])
	{
		if (!ft_strncmp(key, env[i], len))
			return (i);	
		i++;
	}
	return (-1);

}
char *get_process_env(char *key, char **env)
{
	int i;

	i = 0;
	if ((i = env_is_set(key, env)) == -1)
		return (NULL);
	return (get_value(env[i]));
}

char **craft_env(char **base_env, char **to_add)
{
	char		 **fresh;
	int 		tot_len;
	int 		i;
	int			j;

	if (!base_env)
		return (NULL);
	tot_len = ft_ptr_arr_len(base_env) + ft_ptr_arr_len(to_add) + 1;
	if (!(fresh = ft_memalloc(tot_len * sizeof(char*))))
		return (NULL);
	if (!(cpy_array(fresh, base_env)))
		return (NULL);
	i = 0;
	while (to_add[i])
	{
		if ((j = env_is_set(to_add[i], fresh) > -1))
		{
			free(fresh[j]);
			fresh[j] = to_add[i];
		}
		else
			fresh[ft_ptr_arr_len(fresh)] = to_add[i];
		to_add[i] = NULL; /* to avoid double free*/
		i++;	
	}
	//free(base_env);
	return (fresh);
}
