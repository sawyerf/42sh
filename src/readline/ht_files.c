/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:09:25 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/26 15:32:18 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

extern t_list *g_thash[HT_SIZE];

void	ht_refresh(char *path)
{
	int hash;

	if ((hash = ht_hash(path)) < 0)
		return ;
	ft_lstdel(&g_thash[hash]);
	g_thash[hash] = ht_getexec(path);
}

void	ht_refreshall(char *path)
{
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	ht_del();
	if (!(paths = ft_strsplit(path, ':')))
		return ;
	while (paths[i])
	{
		ht_refresh(paths[i]);
		i++;
	}
	ft_tabdel(&paths);
}

int		ht_getfile(char **paths, t_cmd_tab *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		if (!(tmp = ft_zprintf("%s/%s", paths[i], cmd->av[0])))
			return (MEMERR);
		if (!exaccess(tmp))
		{
			ht_hash(paths[i]);
			ft_lstadd(&g_thash[i], ft_lstnew(cmd->av[0], 0));
			cmd->full_path = tmp;
			return (0);
		}
		ft_strdel(&tmp);
		i++;
	}
	return (0);
}

t_list	*ht_getexec(char *path)
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
		if (!(cpath = ft_zprintf("%s/%s", path, ret->d_name)))
			return (NULL);
		if (!folexaccess(cpath))
			ft_lstadd(&lst, ft_lstnew(ret->d_name, ft_strlen(ret->d_name)));
		ft_strdel(&cpath);
	}
	closedir(ptr);
	return (lst);
}
