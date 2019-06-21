/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_matches.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:02:05 by tduval            #+#    #+#             */
/*   Updated: 2019/06/21 19:23:46 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <dirent.h>
#include "libft.h"
#include "ft_patmatch.h"

static void		*free_lst(t_lfiles *lst)
{
	if (lst && lst->next)
		free_lst(lst->next);
	if (lst)
	{
		ft_strdel(&(lst->path));
		ft_memdel((void **)&lst);
	}
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
	t_lfiles	*par;
	char		**res;
	struct stat	buf;
	int			i;

	i = 0;
	while (lst && lst->layer != layer)
		lst = lst->next;
	par = lst;
	while (par)
	{
		if (go_last(par->path)[0] != '.')
			i++;
		par = par->next;
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
			if (pattern[ft_strlen(pattern) -1] == '/')
				res[i] = ft_strjoin(lst->path, "/");
			else
				res[i] = ft_strdup(lst->path);
			i++;
		}
		lst = lst->next;
	}
	free_lst(lst);
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

static t_lfiles	*get_files(t_lfiles *lst, char *pattern, int i)
{
	struct dirent	*files;
	struct stat		buf;
	char			*current_pattern;
	DIR				*dir;
	t_lfiles		*tmp_lst;
	t_lfiles		*subtmp_lst;

	current_pattern = get_current_pattern(pattern);
	tmp_lst = lst;
	while (tmp_lst && tmp_lst->next && tmp_lst->layer != i - 1)
		tmp_lst = tmp_lst->next;
	//ft_printf("pattern au tour %d : %s\n", i, pattern);
	//print_list(lst);
	while (tmp_lst && tmp_lst->layer == i - 1)
	{
		if ((dir = opendir(tmp_lst->path)) != NULL)
		{
			//ft_printf("folder : %s | pattern : %s\n", tmp_lst->path, current_pattern);
			subtmp_lst = tmp_lst;
			while (subtmp_lst && subtmp_lst->next)
				subtmp_lst = subtmp_lst->next;
			while ((files = readdir(dir)) != NULL)
			{
				if (matches(files->d_name, current_pattern)
					&& (ft_strcmp(files->d_name, "..") || ft_strequ(current_pattern, "..") && (ft_strcmp(files->d_name, ".")) || ft_strequ(current_pattern, "..")))
				{
					if (pattern[ft_strlen(pattern) - 1] == '/')
					{
						if (stat(ft_strjoin(ft_strjoin(tmp_lst->path, "/"), files->d_name), &buf) != -1 && S_ISDIR(buf.st_mode))
						{
							if (!(subtmp_lst->next = init_list(get_beginning(tmp_lst->path, files->d_name), i)))
								return (NULL);
							subtmp_lst = subtmp_lst->next;
						}
					}
					else
					{
						if (!(subtmp_lst->next = init_list(get_beginning(tmp_lst->path, files->d_name), i)))
							return (NULL);
						subtmp_lst = subtmp_lst->next;
					}
				}
			}
			closedir(dir);
		}
		tmp_lst = tmp_lst->next;
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
	//ft_printf("LAYERS : %d\n", layer);
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
				ft_putchar('\n');
				i++;
			}
			j++;
		}
	}
	return (0);
}
