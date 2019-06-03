/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 20:59:59 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/03 22:28:18 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include <unistd.h>

t_prompt	g_prompt[] =\
{
	{'u', &pr_gene},
	{'W', &pr_w},
	{'w', &pr_w},
	{'h', &pr_gene},
	{0, &pr_gene}
};

char	*getpwd(void)
{
	char *cpath;
	char *home;

	if (!(cpath = ft_strnew(4095)))
		return (NULL);
	cpath = getcwd(cpath, 4096);
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
		str_addstr(str, getlogin());
	else if (p == 'h')
	{
		if (!(tmp = ft_strnew(25)))
			return ;
		gethostname(tmp, 25);
		str_addstr(str, tmp);
		ft_strdel(&tmp);
	}
}

void	prpt(char *ps, t_stri *str)
{
	int		i;

	while (*ps)
	{
		if (*ps == '\\')
		{
			if (!*ps)
				return ;
			ps++; 
			i = 0;
			while (g_prompt[i].p)
			{
				if (g_prompt[i].p == *ps)
					g_prompt[i].f(str, *ps);
				i++;
			}
		}
		else
			str_add(str, *ps);
		ps++;
	}
}

char	*prompt(void)
{
	char	*ps1;
	t_stri	str;
	
	if (!(ps1 = get_env_value("PS1")))
		return (ft_strdup("$> "));
	str_init(&str);
	prpt(ps1, &str);
	return (str.str);
}
