/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_l_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 19:24:29 by ktlili            #+#    #+#             */
/*   Updated: 2019/05/20 14:15:49 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void		canon_form(char *curpath)
{
	cleandotdot(curpath);
	cleanpath(curpath);
}

static	void	free_buffers(char *pwd, char *curpath)
{
	if (pwd != NULL)
		free(pwd);
	free(curpath);
}

int				handle_pwd_l(char **pwd)
{
	char *env_pwd;
	char *p_pwd;
	char *ret;

	env_pwd = get_env_value("PWD");
	if (!(p_pwd = getcwd(NULL, 0)))
		ft_dprintf(STDERR_FILENO, "21sh : cd : error getting current dir \n");
	if ((p_pwd == NULL) && (env_pwd == NULL))
	{
		*pwd = NULL;
		return (0);
	}
	*pwd = p_pwd;
	if (env_pwd && (!path_access(env_pwd)))
	{
		if (!(ret = ft_strdup(env_pwd)))
			return (MEMERR);
		ft_strdel(&p_pwd);
		*pwd = ret;
	}
	return (0);
}

int				cd_l(char *curpath, char *arg)
{
	char	*pwd;
	int		ret;

	if (handle_pwd_l(&pwd))
		return (MEMERR);
	if ((curpath[0] != '/') && pwd)
	{
		if ((add_slash(&pwd))
			|| (!(curpath = handle_abs_path(pwd, curpath))))
		{
			free(pwd);
			return (MEMERR);
		}
	}
	canon_form(curpath);
	ret = 0;
	if (chdir(curpath))
		ret = cd_dispatch_err(arg, curpath, 0);
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
	if (chdir(curpath))
	{
		cd_dispatch_err(arg, curpath, 1);
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
