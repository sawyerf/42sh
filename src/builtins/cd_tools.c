/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:08:33 by ktlili            #+#    #+#             */
/*   Updated: 2019/05/20 14:15:33 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		cd_error(int errnum, char *arg)
{
	if (errnum == 1)
		ft_dprintf(STDERR_FILENO, "cd: Pathname too long : %s\n", arg);
	else if (errnum == 2)
		ft_dprintf(STDERR_FILENO, "cd : no such file or directory: %s\n", arg);
	else if (errnum == 3)
		ft_dprintf(STDERR_FILENO, "cd: permission denied: %s\n", arg);
	else if (errnum == 4)
		ft_dprintf(STDERR_FILENO, "cd: HOME not set\n");
	else if (errnum == 5)
		ft_dprintf(STDERR_FILENO, "cd: Not a directory: %s\n", arg);
	return (0);
}

int		cd_dispatch_err(char *arg, char *curpath, int freep)
{
	int ret;

	if (arg == NULL)
		arg = curpath;
	if ((ret = path_access(curpath)) != 0)
		cd_error(ret, arg);
	if ((freep) && (curpath))
		free(curpath);
	return (ret);
}

void	update_env_pwd(char *pwd, char *curpath)
{
	if (pwd != NULL)
	{
		set_shell_env("OLDPWD", pwd, 1);
		set_shell_env("PWD", curpath, 1);
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (pwd != NULL)
		{
			set_shell_env("PWD", pwd, 1);
			free(pwd);
		}
	}
}

char	*getoldpwd(void)
{
	char *oldpwd;

	oldpwd = get_env_value("OLDPWD");
	if (oldpwd == NULL)
		return ("\0");
	ft_printf("%s\n", oldpwd);
	return (oldpwd);
}

char	*handle_abs_path(char *pwd, char *curpath)
{
	char *tmp;

	tmp = curpath;
	curpath = ft_strjoin(pwd, curpath);
	ft_strdel(&tmp);
	if (!curpath)
		return (NULL);
	return (curpath);
}
