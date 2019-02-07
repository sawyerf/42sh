/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 14:48:16 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/07 20:41:46 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <dirent.h>
#include <sys/stat.h>

int		exaccess(char *file)
{
		struct stat st;

		if (access(file, F_OK))
			return (-2);
		stat(file, &st);
		if (S_ISDIR(st.st_mode))
			return (-3);
		if (!access(file, X_OK))
			return (0);
		return (-1);
}

int		folexaccess(char *file)
{
		struct stat st;

		if (access(file, F_OK))
			return (-2);
		stat(file, &st);
		if (S_ISDIR(st.st_mode) || !access(file, X_OK))
			return (0);
		return (-1);
}

t_list	*folderin(DIR *ptr, char *path, char *exec, int (*f)(char *file))
{
	struct dirent	*ret;
	t_list			*lst;
	char			*cpath;
	int				len;
	int				count;

	count = 0;
	lst = NULL;
	len = ft_strlen(exec);
	while ((ret = readdir(ptr)))
	{
		cpath = ft_zprintf("%s/%s", path, ret->d_name);
		if (!f(cpath) && !ft_strncmp(ret->d_name, exec, ft_strlen(exec)))
		{
			ft_lstadd(&lst, ft_lstnew(ret->d_name + len, ft_strlen(ret->d_name + len)));
			count++;
		}
		ft_strdel(&cpath);
	}
	if (ret)
		free(ret);
	return (lst);
}

t_list	*get_folex(char *token)
{
	t_list	*lst;
	char	*exec;
	char	*path;
	DIR		*ptr;

	lst = NULL;
	exec = ft_strechr(token, '/') + 1;
	ft_dprintf(2, "%d\n", token - exec);
	path = ft_strndup(exec, token - exec);
	ft_dprintf(2, "%s/%s\n", exec, path);
	if (!(ptr = opendir(path)))
		return (NULL);
	ft_lstadd(&lst, folderin(ptr, path, exec, &folexaccess));
	closedir(ptr);
	return (lst);
}

t_list	*get_exec(char *exec, char *path)
{
	char	**paths;
	int		count;
	DIR		*ptr;
	t_list	*lst;

	lst = NULL;
	if (!(paths = ft_strsplit(path, ':')))
		return (NULL);
	count = 0;
	while (paths[count])
	{
		if (!(ptr = opendir(path)))
			return (NULL);
		ft_lstadd(&lst, folderin(ptr, paths[count], exec, &exaccess));
		closedir(ptr);
		count++;
	}
	return (lst);
}
