/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 14:40:53 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/11 20:52:01 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_list *g_thash[2048];

void	ht_del(void)
{
	int count;

	count = 0;
	while (count < 2048)
	{
		if (g_thash[count])
			ft_lstdel(&g_thash[count]);
		count++;
	}
}

void	ht_init(void)
{
	int	i;

	i = 0;
	while (i < 2056)
	{
		g_thash[i] = NULL;
		i++;
	}
}

int		ht_hash(char *path)
{
	int hash;
	int i;

	hash = 0;
	i = 0;
	if (!path)
		return (-1);
	while (path[i])
	{
		hash += (i + 1) * path[i];
		i++;
	}
	if (i)
		return (hash % 2056);
	return (-1);
}

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

char 	*ht_getvalue(char *path, char *match)
{
	t_list	*tmp;

	if (!(tmp = ht_get(path)))
		return (NULL);
	while (tmp)
	{
		if (!ft_strcmp(match, tmp->content))
			return (ft_strjoin(path, match));
		tmp = tmp->next;
	}
	return (NULL);
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
		cpath = ft_zprintf("%s/%s", path, ret->d_name);
		if (!folexaccess(cpath))
			ft_lstadd(&lst, ft_lstnew(ret->d_name, ft_strlen(ret->d_name)));
		ft_strdel(&cpath);
	}
	if (ret)
		free(ret);
	return (lst);
}

t_list	*ht_get(char *path)
{
	int hash;

	if ((hash = ht_hash(path)) < 0)
		return (NULL);
	if (!g_thash[hash])
	{
		if (!(g_thash[hash] = ht_getexec(path)))
			return (NULL);
	}
	return (g_thash[hash]);
}
