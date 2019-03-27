/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:26:22 by ktlili            #+#    #+#             */
/*   Updated: 2019/03/27 15:17:09 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "hashtable.h"

char	**envdel(char **env, char *var)
{
	int		len;
	int		count;
	int		counta;
	char	**cpy;

	count = 0;
	counta = 0;
	if (!var || !env || (len = ft_strlen(var)) == 0)
		return (env);
	if (!envchrr(env, var))
		return (env);
	if (!(cpy = ft_tabnew(ft_tablen(env) - 1)))
		return (NULL);
	while (env[count])
	{
		if (!(!ft_strncmp(env[count], var, len) && env[count][len] == '='))
		{
			cpy[counta] = env[count];
			counta++;
		}
		else
			ft_strdel(&env[count]);
		count++;
	}
	free(env);
	if (!ft_strncmp(var, "PATH", 4))
		ht_del();
	return (cpy);
}
