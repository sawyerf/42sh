/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 14:48:16 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/25 18:58:47 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <dirent.h>
#include <sys/stat.h>

extern char	*g_builtins[];

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
	if (!path || !(ptr = opendir(path)))
	{
		ft_strdel(&path);
		return (NULL);
	}
	lst = folderin(ptr, path, exec, f);
	ft_strdel(&path);
	closedir(ptr);
	return (lst);
}

t_list	*filterpath(char *exec, t_list *lst)
{
	t_list	*match;
	int		len;

	len = ft_strlen(exec);
	match = NULL;
	while (lst)
	{
		if (!ft_strncmp(exec, lst->content, len))
			ft_lstadd(&match, ft_lstnew(lst->content + len, 0));
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

t_list	*get_builtins(char *exec, t_list *lst)
{
	int		i;
	int		len;

	len = ft_strlen(exec);
	i = 0;
	while (g_builtins[i])
	{
		if (!ft_strncmp(exec, g_builtins[i], len)
			&& !ft_lstisin(lst, g_builtins[i] + len))
			ft_lstadd(&lst, ft_lstnew(g_builtins[i] + len, 0));
		i++;
	}
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
	return (get_builtins(exec, lst));
}
