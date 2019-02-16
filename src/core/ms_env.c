/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 23:11:31 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/15 21:46:10 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
/* maybe ft_varnamelen instead of strlen ?*/
char	*ms_varchr(char **env, char *var)
{
	int		count;

	if (!env || !var)
		return (NULL);
	count = 0;
	while (env[count])
	{
		if (!ft_strncmp(env[count], var, ft_strlen(var)))
			return (env[count] + ft_strlen(var) + 1);
		count++;
	}
	return (NULL);
}

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

char	**ms_shlvl(char **env)
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
