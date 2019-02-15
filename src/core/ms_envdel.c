/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_envdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:26:22 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/15 19:57:12 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "sh_core.h"

char	**ms_envdel(char **env, char *var)
{
	int		len;
	int		count;
	int		counta;
	char	**cpy;

	count = 0;
	counta = 0;
	if (!var || !env || (len = ft_strlen(var)) == 1)
		return (env);
	if (!ms_envchrr(env, var) || !(cpy = ft_tabnew(ft_tablen(env) - 1)))
		return (env);
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
	return (cpy);
}
