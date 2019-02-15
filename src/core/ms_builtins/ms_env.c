/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 23:11:31 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/15 19:10:20 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_envchrr(char **env, char *var)
{
	int count;
	int len;

	if (!var || !env)
		return (NULL);
	len = ft_strlen(var);
	count = 0;
	while (env[count])
	{
		if (!ft_strncmp(env[count], var, len) && env[count][len] == '=')
			return (env[count] + len + 1);
		count++;
	}
	return (NULL);
}

char	**ms_shlv(char **env)
{
	char	*var;
	int		lvl;

	var = NULL;
	var = ms_varchr(env, "SHLVL=");
	if (!var)
		lvl = 1;
	else
		lvl = ft_atoi(var) + 1;
	env = ms_envaddint(env, "SHLVL", lvl);
	return (env);
}
