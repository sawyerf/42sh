/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_l_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 19:24:29 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/04 15:32:46 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void		canon_form(char *curpath)
{
	cleanpath(curpath);
	cleandotdot(curpath);
}

static	void	free_buffers(char *pwd, char *curpath)
{
	if (pwd != NULL)
		free(pwd);
	free(curpath);
}

char			*handle_pwd_l(void)
{
	char *env_pwd;
	char *p_pwd;
	char *ret;

	env_pwd = get_env_value("PWD");
	p_pwd = getcwd(NULL, 0);
	if ((p_pwd == NULL) && (env_pwd == NULL))
		return (NULL);
	if (env_pwd && (!path_access(env_pwd)))
	{
		ret = ft_strdup(env_pwd);
		if (ret == NULL)
			return (p_pwd);
		if (p_pwd)
			free(p_pwd);
		return (ret);
	}
	return (p_pwd);
}

int				cd_l(char *curpath, char *arg)
{
	char	*pwd;
	char	*tmp;
	int		ret;

	pwd = handle_pwd_l();
	if ((curpath[0] != '/') && pwd)
	{
		if (add_slash(&pwd))
			return (MEMERR);
		tmp = curpath;
		curpath = ft_strjoin(pwd, curpath);
		ft_strdel(&tmp);
		if (!curpath)
			free(pwd);
		if (!curpath)
			return (MEMERR);
	}
	canon_form(curpath);
	ret = 0;
	if (chdir(curpath))
		ret = cd_dispatch_err(arg, curpath);
	else
		update_env_pwd(pwd, curpath);
	free_buffers(pwd, curpath);
	return (ret);
}

int				cd_p(char *curpath, char *arg)
{
	char	*tmp_pwd;
	char	*old_pwd;

	tmp_pwd = get_env_value("PWD");
	if (chdir(curpath) != 0)
	{
		cd_dispatch_err(arg, curpath);
		return (0);
	}
	old_pwd = getcwd(NULL, 0);
	if (tmp_pwd != NULL)
		set_shell_env("OLDPWD", tmp_pwd, 1);
	else
		set_shell_env("OLDPWD", old_pwd, 1);
	if (old_pwd != NULL)
		free(old_pwd);
	tmp_pwd = getcwd(NULL, 0);
	set_shell_env("PWD", tmp_pwd, 1);
	if (tmp_pwd != NULL)
		free(tmp_pwd);
	free(curpath);
	return (0);
}
