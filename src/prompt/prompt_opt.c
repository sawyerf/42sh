/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_opt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:56:25 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/27 19:57:52 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

char	*getpwd(void)
{
	char	*cpath;
	char	*home;

	if (!(cpath = ft_strnew(4095)))
		return (NULL);
	getcwd(cpath, 4094);
	home = get_env_value("HOME");
	if (!ft_strcmp(home, cpath))
		ft_strcpy(cpath, "~");
	return (cpath);
}

char	*getfold(void)
{
	char	*cpath;
	char	*ret;
	int		i;

	if (!(cpath = getpwd()))
		return (NULL);
	i = ft_strlen(cpath);
	if (!ft_strcmp(cpath, "/"))
		return (cpath);
	while (i >= 0 && cpath[i] != '/')
		i--;
	ret = ft_strdup(cpath + i + 1);
	ft_strdel(&cpath);
	return (ret);
}

void	pr_version(t_stri *str, char p)
{
	if (p == 'v')
		str_addstr(str, SH_VERS);
	else if (p == 's')
		str_addstr(str, SH_NAME);
}

void	pr_w(t_stri *str, char p)
{
	char	*tmp;

	if (p == 'W')
	{
		tmp = getfold();
		str_addstr(str, tmp);
	}
	else if (p == 'w')
	{
		tmp = getpwd();
		str_addstr(str, tmp);
	}
	ft_strdel(&tmp);
}

void	pr_gene(t_stri *str, char p)
{
	char *tmp;

	if (p == '\\')
		str_add(str, '\\');
	else if (p == 'u')
	{
		tmp = getlogin();
		str_addstr(str, tmp);
	}
	else if (p == 'h')
	{
		if (!(tmp = ft_strnew(25)))
			return ;
		gethostname(tmp, 25);
		str_addstr(str, tmp);
		ft_strdel(&tmp);
	}
	else if (p == 'n')
		str_add(str, '\n');
}
