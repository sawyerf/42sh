/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   craft_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:22:06 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/09 21:15:13 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

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

int			env_is_set(char *key, char **env)
{
	int	i;
	int	len;

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

char		*get_process_env(char *key, char **env)
{
	int i;

	i = 0;
	if ((i = env_is_set(key, env)) == -1)
		return (NULL);
	return (get_value(env[i]));
}

void		replace_var(char **fresh, char *to_add)
{
	free(*fresh);
	*fresh = to_add;
}

char		**craft_env(char **base_env, char **to_add)
{
	char	**fresh;
	int		tot_len;
	int		i;
	int		j;

	if (!base_env)
		return (NULL);
	tot_len = ft_tablen(base_env) + ft_tablen(to_add) + 1;
	if (!(fresh = ft_memalloc(tot_len * sizeof(char*))))
		return (NULL);
	if (!(cpy_array(fresh, base_env)))
		return (NULL);
	i = 0;
	while (to_add[i])
	{
		if (((j = env_is_set(to_add[i], fresh)) > -1))
			replace_var(fresh + j, to_add[i]);
		else
			fresh[ft_tablen(fresh)] = to_add[i];
		to_add[i] = NULL;
		i++;
	}
	return (fresh);
}
