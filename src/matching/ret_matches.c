/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_matches.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:02:05 by tduval            #+#    #+#             */
/*   Updated: 2019/06/18 22:35:05 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"
#include "ft_patmatch.h"

static int		get_layer(char *pattern)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (pattern[i])
	{
		if (pattern[i] == '/' && pattern[i + 1])
			r++;
		i++;
	}
	return (r);
}

static char		*get_curpat(char *pattern)
{
	int		i;

	i = 0;
	while (pattern[i] && pattern[i] != '/')
		i++;
	return (ft_strsub(pattern, 0, i));
}

static t_lfiles	*init_list(char *path, int layer)
{
	t_lfiles	*res;

	if (!(res = (t_lfiles *)ft_memalloc(sizeof(t_lfiles))))
		return (NULL);
	res->layer = layer;
	if (layer == -1)
	{
		if (path[0] == '/')
			res->path = ft_strdup("/");
		else
			res->path = ft_strdup("./");
	}
	else
		res->path = path;
	res->next = NULL;
	return (res);
}

static char		*go_after(char *str)
{
	while (*str && *str != '/')
		str++;
	return (str ? str + 1 : NULL);
}

static char		*get_beginning(char *lpath, char *dname)
{
	char	*ret;
	char	*tmp;

	if (lpath[ft_strlen(lpath) - 1] != '/')
		tmp = ft_strjoin(lpath, "/");
	else
		tmp = ft_strdup(lpath);
	ret = ft_strjoin(tmp, dname);
	ft_strdel(&tmp);
	return (ret);
}

static char		*go_last(char *str)
{
	while (strchr(str, '/'))
		str++;
	return(str);
}

static char		**final_step(t_lfiles *lst, int layer, char *pattern)
{
	t_lfiles	*par;
	char		**res;
	int			i;

	i = 0;
	while (lst && lst->layer != layer)
		lst = lst->next;
	par = lst;
	while (par)
	{
		par = par->next;
		i++;
	}
	if (!(res = (char **)ft_memalloc(sizeof(char *) * (i + 2))))
		return (NULL);
	if (i == 0)
	{
		res[i] = ft_strdup(pattern);
		return (res);
	}
	par = lst;
	i = 0;
	while (lst)
	{
		if (go_last(lst->path)[0] != '.')
		{
			res[i] = pattern[0] == '/' ? ft_strdup(lst->path) : ft_strdup(lst->path + 2);
			i++;
		}
		lst = lst->next;
	}
	return (res);
}

char			**ret_matches(char *pattern)
{
	struct dirent	*files;
	t_lfiles		*list;
	t_lfiles		*par;
	t_lfiles		*par2;
	DIR				*dir;
	char			**res;
	char			*curpath;
	char			*ori;
	char			*curpat;
	int				layer;
	int				i;

	i = 0;
	res = NULL;
	list = init_list(pattern, -1);
	ori = pattern;
	if (pattern[0] == '/')
		pattern++;
	layer = get_layer(pattern);
	while (i <= layer && list)
	{
		curpat = get_curpat(pattern);
		par = list;
		while (par && par->next && par->layer != i)
			par = par->next;
		while (par && par->layer == i - 1)
		{
			if ((dir = opendir(par->path)) != NULL)
			{
				par2 = par;
				while (par2 && par2->next)
					par2 = par2->next;
				while ((files = readdir(dir)) != NULL)
				{
					if (matches(files->d_name, curpat))
					{
						if (!(par2->next = init_list(get_beginning(par->path, files->d_name), i)))
							return (NULL);
						par2 = par2->next;
					}
				}
				closedir(dir);
			}
			par = par->next;
		}
		pattern = go_after(pattern);
		i++;
	}
	return (final_step(list, layer, ori));
}
int		main(int ac, char **av)
{
	char	**test;
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (ac > 1)
	{
		while (j < ac)
		{
			i = 0;
			test = ret_matches(av[j]);
			while (test && test[i])
			{
				ft_putstr(test[i]);
				ft_putchar('\n');
				i++;
			}
			j++;
		}
	}
	return (0);
}
