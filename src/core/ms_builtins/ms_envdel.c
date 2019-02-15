/ ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_envdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 23:37:58 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/15 18:36:49 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
