/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envadd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <apeyret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 21:55:42 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/24 17:57:53 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "hashtable.h"

int		envadd(char ***env, char *var)
{
	char	**cpenv;
	int		len;

	len = ft_tablen(*env) + 1;
	if (!(cpenv = ft_tabnew(len)))
		return (MEMERR);
	cpenv = ms_tabcpy(cpenv, *env);
	if (!(cpenv[len - 1] = ft_strdup(var)))
	{
		ft_tabdel(&cpenv);
		return (MEMERR);
	}
	cpenv[len] = NULL;
	free(*env);
	*env = cpenv;
	return (0);
}

int		csetenv(char ***env, char *var)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strchr(var, '=') - var + 1;
	if (!ft_strncmp(var, "PATH=", 5))
		ht_del();
	while (*env && (*env)[count])
	{
		if (!ft_strncmp(var, (*env)[count], len))
		{
			ft_strdel(&(*env)[count]);
			if (!((*env)[count] = ft_strdup(var)))
			{
				ft_tabdel(env);
				return (MEMERR);
			}
			return (0);
		}
		count++;
	}
	if (!*env || !(*env)[count])
		return (envadd(env, var));
	return (0);
}

int		envaddint(char ***env, char *var, int value)
{
	char	*add;
	int		ret; // why?

	add = NULL;
	if (!(add = ft_zprintf("%s=%d", var, value)))
		return (MEMERR);
	ret = csetenv(env, add);
	ft_strdel(&add);
	if (ret)
		return (ret);
	return (0);
}

int		envaddstr(char ***env, char *var, char *value)
{
	log_info("ENV__ADD var : [%s] | value : [%s]", var, value);
	char		*add;

	if (!value)
		return (0);
	add = NULL;
	if (!(add = ft_zprintf("%s=%s", var, value)))
		return (MEMERR);
	if (csetenv(env, add) == MEMERR)
	{
		ft_strdel(&add);
		return (MEMERR);
	}
	ft_strdel(&add);
	return (0);
}
