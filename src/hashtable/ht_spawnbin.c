/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_spawnbin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 16:12:50 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/22 19:41:59 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

extern t_list *g_thash[];


t_list	*ht_getghash(char *path)
{
	int		hash;

	if ((hash = ht_hash(path)) >= 0)
		return (g_thash[hash]);
	return (NULL);
}

int		ht_addpath(char	*path, char *npath)
{
	int		hash;
	t_list	*lst;

	hash = ht_hash(path);
	if (!(lst = ft_lstnew(npath, ft_strlen(path) + 1)))
		return (MEMERR);
	ft_lstadd(&g_thash[hash], lst);
	return (0);
}

int		ht_getfile(char **paths, t_cmd_tab *cmd)
{
	int		i;
	int		ret[2];
	char	*tmp;

	i = 0;
	ret[0] = 0;
	ret[1] = br_NOTFOUND;
	while (paths[i])
	{
		if (!(tmp = ft_zprintf("%s/%s", paths[i], cmd->av[0])))
			return (MEMERR);
		if (!(ret[0] = exaccess(tmp)))
		{
			if (ht_addpath(paths[i], tmp) == MEMERR)
				return (MEMERR);
			ft_strdel(&cmd->full_path);
			cmd->full_path = tmp;
			return (0);
		}
		ft_strdel(&cmd->full_path);
		cmd->full_path = tmp;
		if (ret[0] != br_NOTFOUND)
			ret[1] = ret[0];
		i++;
	}
	return (ret[1]);
}

char	*ht_getpath(char **paths, char *exec)
{
	t_list	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ht_getghash(paths[i]);
		while (tmp)
		{
			if (!ft_strcmp(exec, tmp->content + tmp->content_size))
			{
				if (!exaccess(tmp->content))
					return (tmp->content);
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (NULL);
}

int		ht_getvalue(char *path, t_cmd_tab *cmd)
{
	char	*result;
	char	**paths;
	int		ret;

	if (ft_cisin(cmd->av[0], '/'))
		return (exaccess(cmd->av[0]));
	if (!(paths = ft_strsplit(path, ':')))
		return (MEMERR);
	if ((result = ht_getpath(paths, cmd->av[0])))
	{
		if (!(cmd->full_path = ft_strdup(result)))
			return (MEMERR);
		return (0);
	}
	ret = ht_getfile(paths, cmd);
	free_tab(paths);
	return (ret);
}
