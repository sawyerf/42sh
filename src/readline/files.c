/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 14:48:16 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/29 19:04:37 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <dirent.h>
#include <sys/stat.h>

int		exaccess(char *file)
{
	struct stat st;

	if (access(file, F_OK))
		return (2);
	stat(file, &st);
	if (S_ISDIR(st.st_mode))
		return (3);
	if (!access(file, X_OK))
		return (0);
	return (1);
}

int		filexist(char *file)
{
	if (access(file, F_OK))
		return (2);
	return (0);
}

int		folexaccess(char *file)
{
	struct stat st;

	if (access(file, F_OK))
		return (2);
	stat(file, &st);
	if (S_ISDIR(st.st_mode))
		return (0);
	if (!access(file, X_OK))
		return (0);
	return (1);
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
		if (!(cpath = ft_zprintf("%s/%s", path, ret->d_name)))
			continue ;
		if (!f(cpath) && !ft_strncmp(ret->d_name, exec, ft_strlen(exec))
				&& ft_strcmp(ret->d_name, "..") && ft_strcmp(ret->d_name, "."))
		{
			ft_lstadd(&lst, ft_lstnew(ret->d_name + len, exaccess(cpath)));
			count++;
		}
		ft_strdel(&cpath);
	}
	return (lst);
}

t_list	*get_folex(char *token, int (*f)(char *file))
{
	t_list	*lst;
	char	*exec;
	char	*path;
	DIR		*ptr;

	exec = ft_strechr(token, '/');
	(exec[0] == '/') ? exec++ : 0;
	if (exec - token)
		path = ft_strndup(token, exec - token);
	else
		path = ft_strdup(".");
	if (!(ptr = opendir(path)))
		return (NULL);
	lst = folderin(ptr, path, exec, f);
	ft_strdel(&path);
	closedir(ptr);
	return (lst);
}

t_list	*filterpath(char *exec, t_list *lst)
{
	t_list	*match;
//	t_list	*tmp;
	int		len;

	len = ft_strlen(exec);
	match = NULL;
	while (lst)
	{
		if (!ft_strncmp(exec, lst->content, len))
			ft_lstadd(&match, ft_lstnew(lst->content + len, 0));
//		tmp = lst;
		lst = lst->next;
	}
	return (match);
}

t_list	*hst_getexec(char *path)
{
	t_list			*lst;
	DIR				*ptr;
	struct dirent	*ret;
	char			*cpath;

	lst = NULL;
	if (!(ptr = opendir(path)))
		return (NULL);
	while ((ret = readdir(ptr)))
	{
		if (!ft_strcmp(ret->d_name, "..") || !ft_strcmp(ret->d_name, "."))
			continue;
		if (!(cpath = ft_zprintf("%s/%s", path, ret->d_name)))
			return (NULL);
		if (!exaccess(cpath))
			ft_lstadd(&lst, ft_lstnew(ret->d_name, 0));
		ft_strdel(&cpath);
	}
	closedir(ptr);
	return (lst);
}

t_list	*get_exec(char *exec, char *path)
{
	char	**paths;
	int		count;
	t_list	*lst;
	t_list	*tmp;

	if (exec[0] == '/' || !ft_strncmp("./", exec, 2))
		return (get_folex(exec, &folexaccess));
	lst = NULL;
	if (!(paths = ft_strsplit(path, ':')))
		return (NULL);
	count = 0;
	while (paths[count])
	{
		tmp = hst_getexec(paths[count]);
		ft_lstadd(&lst, filterpath(exec, tmp));
		ft_lstdel(&tmp);
		count++;
	}
	ft_tabdel(&paths);
	return (lst);
}
