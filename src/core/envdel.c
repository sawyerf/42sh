/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envdel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 21:55:21 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/04 15:45:19 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "hashtable.h"

char	**envdel(char **env, char *var)
{
	int		len;
	int		i[2];
	char	**cpy;

	i[0] = 0;
	i[1] = 0;
	if (!var || !env || (len = ft_strlen(var)) == 0 || !envchrr(env, var))
		return (env);
	if (!(cpy = ft_tabnew(ft_tablen(env) - 1)))
		return (NULL);
	while (env[i[0]])
	{
		if (!(!ft_strncmp(env[i[0]], var, len) && env[i[0]][len] == '='))
		{
			cpy[i[1]] = env[i[0]];
			i[1]++;
		}
		else
			ft_strdel(&env[i[0]]);
		i[0]++;
	}
	free(env);
	if (!ft_strncmp(var, "PATH", 4))
		ht_del();
	return (cpy);
}
