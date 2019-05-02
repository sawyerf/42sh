/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envadd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 21:55:42 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/29 21:56:43 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "hashtable.h"

char	**envadd(char **env, char *var)
{
	char	**cpenv;
	int		len;

	len = ft_tablen(env) + 1;
	if (!(cpenv = ft_tabnew(len)))
		return (NULL);
	cpenv = ms_tabcpy(cpenv, env);
	if (!(cpenv[len - 1] = ft_strdup(var)))
		return (NULL);
	cpenv[len] = NULL;
	free(env);
	return (cpenv);
}

char	**csetenv(char **env, char *var)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strchr(var, '=') - var + 1;
	if (!ft_strncmp(var, "PATH=", 5))
		ht_del();
	if (!env)
		return (envadd(env, var));
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
		return (envadd(env, var));
	return (env);
}

char	**envaddint(char **env, char *var, int value)
{
	char *add;

	add = NULL;
	if (!(add = ft_zprintf("%s=%d", var, value)))
		return (NULL);
	env = csetenv(env, add);
	ft_strdel(&add);
	return (env);
}

char	**envaddstr(char **env, char *var, char *value)
{
	char		*add;
	static char	*empty = "";

	if (!value)
		value = empty;
	add = NULL;
	if (!(add = ft_zprintf("%s=%s", var, value)))
		return (NULL);
	env = csetenv(env, add);
	ft_strdel(&add);
	return (env);
}
