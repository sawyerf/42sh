/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:09:25 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/25 16:34:56 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include <dirent.h>

extern t_list *g_thash[HT_SIZE];

int		ht_refresh(char *path)
{
	int hash;

	if ((hash = ht_hash(path)) < 0)
		return (0);
	ft_lstdel(&g_thash[hash]);
	if (ht_getexec(path, &g_thash[hash]) == MEMERR)
		return (MEMERR);
	return (0);
}

int		ht_refreshall(char *path)
{
	char	**paths;
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	paths = NULL;
	ht_del();
	if (!(paths = ft_strsplit(path, ':')))
		return (MEMERR);
	while (paths[i] && !ret)
	{
		if (ht_refresh(paths[i]) == MEMERR)
			ret = MEMERR;
		i++;
	}
	ft_tabdel(&paths);
	return (ret);
}

int		ht_addfile(char **paths, char *exec)
{
	int		i;
	int		hash;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		if (!(tmp = ft_zprintf("%s/%s", paths[i], exec)))
			return (MEMERR);
		if (!exaccess(tmp))
		{
			hash = ht_hash(paths[i]);
			ft_lstadd(&g_thash[hash], ft_lstnew(tmp, ft_strlen(paths[i]) + 1));
			ft_strdel(&tmp);
			return (0);
		}
		ft_strdel(&tmp);
		i++;
	}
	return (0);
}

int		ht_getexec(char *path, t_list **lst)
{
	DIR				*ptr;
	struct dirent	*ret;
	char			*cpath;
	t_list			*tmp;

	*lst = NULL;
	if (!(ptr = opendir(path)))
		return (0);
	while ((ret = readdir(ptr)))
	{
		if (!ft_strcmp(ret->d_name, "..") || !ft_strcmp(ret->d_name, "."))
			continue;
		if (!(cpath = ft_zprintf("%s/%s", path, ret->d_name)) && (closedir(ptr) || 1))
			return (MEMERR);
		if (!exaccess(cpath))
		{
			if (!(tmp = ft_lstnew(cpath, ft_strlen(path) + 1)) && ft_strdel(&cpath))
				return (MEMERR);
			ft_lstadd(lst, tmp);
		}
		ft_strdel(&cpath);
	}
	closedir(ptr);
	return (0);
}
