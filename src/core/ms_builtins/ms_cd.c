/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 19:32:31 by apeyret           #+#    #+#             */
/*   Updated: 2019/01/14 19:33:33 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_pathjoin(char *p1, char *p2)
{
	char *cpath;

	if (!(cpath = ft_zprintf("%s/%s", p1, p2)))
		return (NULL);
	ft_strdel(&p1);
	return (cpath);
}

char	*ms_getpwd(void)
{
	char *cpath;

	if (!(cpath = ft_strnew(4095)))
		return (NULL);
	cpath = getcwd(cpath, 4096);
	return (cpath);
}

int		ms_chdir(char *path, char *cpath, char ***env)
{
	char	*var;

	var = NULL;
	if (ms_foaccess(cpath))
	{
		ft_dprintf(2, "msh: cd: %s: No such file or directory\n", path);
		ft_strdel(&cpath);
		return (1);
	}
	if ((var = ms_varchr(*env, "PWD=")))
		*env = ms_envaddstr(*env, "OLDPWD", var);
	chdir(cpath);
	ft_strdel(&cpath);
	if (!(cpath = ft_strnew(4095)))
		return (1);
	cpath = getcwd(cpath, 4096);
	*env = ms_envaddstr(*env, "PWD", cpath);
	ft_strdel(&cpath);
	return (0);
}

int		ms_cd(char *path, char ***env)
{
	char	*cpath;

	if (!path)
	{
		if (!ms_varchr(*env, "HOME="))
			return (ft_preturn(1, ft_dprintf(2, "bash: cd: HOME not set\n")));
		cpath = ft_strdup(ms_varchr(*env, "HOME="));
	}
	else if (!ft_strcmp(path, "-"))
	{
		if (!(cpath = ms_varchr(*env, "OLDPWD=")))
			return (ft_preturn(1, ft_dprintf(2, "bash: cd OLDPWD not set\n")));
		if (!(ms_cd(cpath, env)))
			return (ft_preturn(0, ft_printf("%s\n", ms_varchr(*env, "PWD="))));
		return (1);
	}
	else if (path[0] != '/')
	{
		if (!(cpath = ms_getpwd()))
			return (1);
		cpath = ms_pathjoin(cpath, path);
	}
	else
		cpath = ft_strdup(path);
	return (ms_chdir(path, cpath, env));
}
