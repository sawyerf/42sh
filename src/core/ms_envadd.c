/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_envadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 23:36:39 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/19 18:41:29 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

char	**ms_envadd(char **env, char *var)
{
	char	**cpenv;
	int		len;

	len = ft_tablen(env) + 1;
	if (!(cpenv = ft_tabnew(len)))
		return (NULL); // should be returning NULL
	cpenv = ms_tabcpy(cpenv, env);
	if (!(cpenv[len - 1] = ft_strdup(var)))
		return (NULL);
	cpenv[len] = NULL;
	free(env);
	return (cpenv);
}

char	**ms_csetenv(char **env, char *var)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strchr(var, '=') - var + 1;
	if (!env)
		return (ms_envadd(env, var));
	while (env[count])
	{
		if (!ft_strncmp(var, env[count], len))
		{
			ft_strdel(&env[count]);
			if (!(env[count] = ft_strdup(var)))
				return (NULL);
			return (env);
		}
		count++;
	}
	if (!env[count])
		return (ms_envadd(env, var));
	return (env);
}

char	**ms_envaddint(char **env, char *var, int value)
{
	char *add;

	add = NULL;
	if (!(add = ft_zprintf("%s=%d", var, value)))
		return (NULL);
	env = ms_csetenv(env, add);
	ft_strdel(&add);
	return (env);
}

char	**ms_envaddstr(char **env, char *var, char *value)
{
	char *add;

		add = NULL;
	if (!(add = ft_zprintf("%s=%s", var, value)))
		return (NULL);
	env = ms_csetenv(env, add);
	ft_strdel(&add);
	return (env);
}
