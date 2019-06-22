/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_matches.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:02:05 by tduval            #+#    #+#             */
/*   Updated: 2019/06/22 03:22:05 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <dirent.h>
#include "libft.h"
#include "ft_patmatch.h"

static void	*free_lst(t_lfiles *lst)
{
	if (lst && lst->next)
		free_lst(lst->next);
	if (lst)
	{
		ft_strdel(&lst->path);
		ft_memdel((void **)&lst);
	}
	return (NULL);
}

static char		*go_after(char *str)
{
	int		i;

	i = 0;
	while (str && str[i] && str[i] != '/')
		i++;
	while (str && str[i] && str[i + 1] && str[i + 1] == '/')
		i++;
	return (str && str[i] ? str + i + 1 : NULL);
}

static char		*get_current_pattern(char *pattern)
{
	int		i;

	i = 0;
	while (pattern && pattern[i] && pattern[i] != '/')
		i++;
	return (ft_strsub(pattern, 0, i));
}

static char		*ft_strremoveat(char *str, int i)
{
	int		j;

	j = 0;
	while (str[j])
	{
		if (j >= i)
			str[j] = str[j + 1];
		else
			str[j] = str[j];
		j++;
	}
	return (str);
}

static int		get_layer(char *pattern)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (pattern[i])
	{
		if (pattern[i] == '/' && pattern[i + 1] && pattern[i + 1] != '/')
			r++;
		i++;
	}
	return (r);
}

static char		*format_pattern(char *pattern)
{
	int		i;

	i = 0;
	while (pattern[i])
	{
		if (pattern[i] == '.'
				&& pattern[i + 1] == '/'
				&& (i == 0 || pattern[i - 1] == '/'))
		{
			pattern = ft_strremoveat(pattern, i);
			pattern = ft_strremoveat(pattern, i);
		}
		else
			i++;
	}
	return (pattern);
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
		res->path = format_pattern(path);
	res->next = NULL;
	return (res);
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
	t_lfiles	*origin;
	t_lfiles	*tmp;
	char		**res;
	struct stat	buf;
	int			i;
	int			f;

	i = 0;
	f = pattern[ft_strlen(pattern) - 1] == '/' ? 1 : 0;
	origin = lst;
	while (lst && lst->layer != layer)
		lst = lst->next;
	tmp = lst;
	while (tmp)
	{
		if (go_last(tmp->path)[0] != '.')
			i++;
		tmp= tmp->next;
	}
	if (!(res = (char **)ft_memalloc(sizeof(char *) * (i + 2))))
		return (free_lst(lst));
	if (i == 0)
	{
		res[i] = pattern;
		free_lst(lst);
		return (res);
	}
	else
		ft_strdel(&pattern);
	tmp = lst;
	i = 0;
	while (tmp)
	{
		if (go_last(tmp->path)[0] != '.')
		{
			if (f && !(res[i] = ft_strjoin(tmp->path, "/")))
				return (free_lst(origin));
			else
			{
				if (!(res[i] = ft_strdup(tmp->path)))
					return (free_lst(origin));
			}
			i++;
		}
		tmp = tmp->next;
	}
	free_lst(origin);
	return (res);
}

void	print_list(t_lfiles *lst)
{
	while (lst)
	{
		ft_printf("layer : %d | %s\n", lst->layer, lst->path);
		lst = lst->next;
	}
}

static int	append_file(t_lfiles *lists[2], char *str[4], struct dirent *files, int i)
{
	struct stat	buf;

	if (str[PATTERN][ft_strlen(str[PATTERN]) - 1] == '/')
	{
		if ((!(str[TMP1] = ft_strjoin(lists[TMP_LST]->path, "/")))
				|| !(str[TMP2] = ft_strjoin(str[TMP1], files->d_name)))
		{
				ft_strdel(&str[TMP1]);
				return (0);
		}
		if (stat(str[TMP2], &buf) != -1 && S_ISDIR(buf.st_mode))
		{
			if (!(lists[SUBTMP_LST]->next = init_list(get_beginning(lists[TMP_LST]->path, files->d_name), i)))
					return (0);
			lists[SUBTMP_LST] = lists[SUBTMP_LST]->next;
		}
		ft_strdel(&str[TMP1]);
		ft_strdel(&str[TMP2]);
	}
	else
	{
		if (!(lists[SUBTMP_LST]->next = init_list(get_beginning(lists[TMP_LST]->path, files->d_name), i)))
			return (0);
		lists[SUBTMP_LST] = lists[SUBTMP_LST]->next;
	}
	return (1);
}

static t_lfiles	*get_files(t_lfiles *lst, char *pattern, int i)
{
	t_lfiles		*lists[2];
	char			*str[4];
	struct dirent	*files;
	struct stat		buf;
	DIR				*dir;

	str[TMP1] = NULL;
	str[TMP2] = NULL;
	str[PATTERN] = pattern;
	str[CURPATTERN] = get_current_pattern(str[PATTERN]);
	lists[TMP_LST] = lst;
	while (lists[TMP_LST]&& lists[TMP_LST]->next && lists[TMP_LST]->layer != i - 1)
		lists[TMP_LST]= lists[TMP_LST]->next;
	while (lists[TMP_LST] && lists[TMP_LST]->layer == i - 1)
	{
		if ((dir = opendir(lists[TMP_LST]->path)) != NULL)
		{
			lists[SUBTMP_LST] = lists[TMP_LST];
			while (lists[SUBTMP_LST] && lists[SUBTMP_LST]->next)
				lists[SUBTMP_LST] = lists[SUBTMP_LST]->next;
			while ((files = readdir(dir)) != NULL)
			{
				if (matches(files->d_name, str[CURPATTERN])
						&& (ft_strcmp(files->d_name, "..") || ft_strequ(str[CURPATTERN], "..")
						&& (ft_strcmp(files->d_name, ".")) || ft_strequ(str[CURPATTERN], ".")))
				{
					if (!(append_file(lists, str, files, i)))
						return (NULL);
				}
			}
			closedir(dir);
		}
		lists[TMP_LST] = lists[TMP_LST]->next;
	}
	return (lst);
}

char			**ret_matches(char *pattern)
{
	struct dirent	*files;
	t_lfiles		*lst;
	char			*origin;
	int				layer;
	int				i;

	i = 0;
	origin = ft_strdup(pattern);
	pattern = format_pattern(pattern);
	lst = init_list(pattern, -1);
	if (pattern[0] == '/')
	{
		while (pattern && *pattern && *pattern == '/')
			pattern++;
	}
	layer = get_layer(pattern);
	while (i <= layer && lst)
	{
		if (!(lst = get_files(lst, pattern, i)))
			return (NULL);
		pattern = go_after(pattern);
		i++;
	}
	return (final_step(lst, layer, origin));
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
				ft_strdel(&test[i]);
				ft_putchar('\n');
				i++;
			}
			j++;
		}
	}
	ft_memdel((void **)&test);
	return (0);
}
