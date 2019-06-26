/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_matches.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:02:05 by tduval            #+#    #+#             */
/*   Updated: 2019/06/26 04:51:56 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <dirent.h>
#include "libft.h"
#include "ft_patmatch.h"

static char		*get_current_pattern(char *pattern)
{
	int		i;

	i = 0;
	while (pattern && pattern[i] && pattern[i] != '/')
		i++;
	return (ft_strsub(pattern, 0, i));
}

char		*ft_strremoveat(char *str, int i)
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

char		*format_pattern(char *pattern)
{
	int		i;

	i = 0;
	while (pattern && pattern[i])
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
		res->path = path;
	res->next = NULL;
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
	char		*tmp;

	if (str[PATTERN][ft_strlen(str[PATTERN]) - 1] == '/')
	{
		if ((!(str[TMP1] = ft_strjoin(lists[TMP_LST]->path, "/")))
				|| !(str[TMP2] = ft_strjoin(str[TMP1], files->d_name)))
				return ((int)free_all(str[TMP1], NULL, NULL, NULL));
		if (stat(str[TMP2], &buf) != -1 && S_ISDIR(buf.st_mode))
		{
			if (!(tmp =get_beginning(lists[TMP_LST]->path, files->d_name)))
				return ((int)free_all(str[0], str[1], str[2], NULL));
			if (!(lists[SUBTMP_LST]->next = init_list(ft_strjoin(tmp, "/"), i)))
					return ((int)free_all(str[0], str[1], tmp, NULL));
			ft_strdel(&tmp);
			lists[SUBTMP_LST] = lists[SUBTMP_LST]->next;
		}
		free_all(str[TMP1], str[TMP2], NULL, NULL);
	}
	else
	{
		if (!(lists[SUBTMP_LST]->next = init_list(
				get_beginning(lists[TMP_LST]->path, files->d_name), i)))
			return ((int)free_all(str[0], str[1], str[2], NULL));
		lists[SUBTMP_LST] = lists[SUBTMP_LST]->next;
	}
	return (1);
}

static t_lfiles	*get_files(t_lfiles *lst, char *pattern, int i, int layer)
{
	t_lfiles		*lists[2];
	char			*str[4];
	struct dirent	*files;
	struct stat		buf;
	DIR				*dir;

	str[TMP1] = NULL;
	str[TMP2] = NULL;
	str[PATTERN] = pattern;
	lists[TMP_LST] = lst;
	if (!(str[CURPATTERN] = get_current_pattern(str[PATTERN])))
		return (NULL);
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
				if (matches(files->d_name, str[CURPATTERN], 0)
						&& ((ft_strcmp(files->d_name, "..") || str[CURPATTERN][0] == '.')
						&& ((ft_strcmp(files->d_name, ".")) || str[CURPATTERN][0] == '.')
						&& ((files->d_name[0] != '.' || str[CURPATTERN][0] == '.'))
						&& (!(append_file(lists, str, files, i)))))
							return (NULL);
			}
			closedir(dir);
		}
		lists[TMP_LST] = lists[TMP_LST]->next;
	}
	free(str[CURPATTERN]);
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
	if (!(origin = ft_strdup(pattern)))
		return (NULL);
	pattern = format_pattern(pattern);
	if (!(lst = init_list(pattern, -1)))
		return ((char **)free_all(origin, NULL, NULL, NULL));
	if (pattern[0] == '/')
	{
		while (pattern && *pattern && *pattern == '/')
			pattern++;
	}
	layer = get_layer(pattern);
	while (i <= layer && lst)
	{
		if (!(lst = get_files(lst, pattern, i, layer)))
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
