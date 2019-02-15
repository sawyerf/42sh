/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_bienv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 23:34:11 by apeyret           #+#    #+#             */
/*   Updated: 2019/01/15 19:37:40 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ms_env(char **av, char **env)
{
	(void)av;
	ft_puttab(env);
	return (0);
}

int		ms_unsetenv(char **av, char ***env)
{
	int count;
	int ret;

	ret = 0;
	count = 0;
	if (!av || !*env)
		return (1);
	while (av[count])
	{
		if (!ms_varcheck(av[count]))
		{
			ft_printf("msh: unsetenv: '%s': not a valid identifier\n",
				av[count]);
			ret = 1;
		}
		else
			*env = ms_envdel(*env, av[count]);
		count++;
	}
	return (ret);
}

int		ms_setenv(char **av, char ***env)
{
	int		count;

	count = 0;
	if (!av || !*env)
		return (1);
	while (av[count])
	{
		if (!ms_varcheckequ(av[count]))
			ft_printf("msh: setenv: `%s': not a valid identifier\n",
				av[count]);
		if (ft_cisin(av[count], '='))
			*env = ms_csetenv(*env, av[count]);
		count++;
	}
	return (0);
}
