/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */ /*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 14:40:53 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/12 13:59:18 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "ft_eval.h"

t_list *g_thash[HT_SIZE];

void	ht_del(void)
{
	int count;

	count = 0;
	while (count < HT_SIZE)
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
	while (i < HT_SIZE)
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
		return (hash % HT_SIZE);
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

int		ht_getfile(char **paths, t_cmd_tab *cmd)
{
	int		i;
	char	*tmp;
	int		hash;

	i = 0;
	while (paths[i])
	{
		if (!(tmp = ft_zprintf("%s/%s", paths[i], cmd->av[0])))
			return (MEMERR);
		if (!exaccess(tmp))
		{
			hash = ht_hash(paths[i]);
			ft_lstadd(&g_thash[i], ft_lstnew(cmd->av[0], 0));
			cmd->full_path = tmp;
			return (0);
		}
		ft_strdel(&tmp);
		i++;
	}
	return (0);
}

int		ht_getvalue(char *path, t_cmd_tab *cmd)
{
	t_list	*tmp;
	char	*file;
	char	**paths;
	int		i;

	i = 0;
	if (!(paths = ft_strsplit(path, ':')))
		return (MEMERR);
	while (paths[i])
	{
		tmp = ht_get(paths[i]);
		while (tmp)
		{
			if (!ft_strcmp(cmd->av[0], tmp->content))
			{
				if (!(file = ft_zprintf("%s/%s", paths[i], tmp->content)))
					return (MEMERR);
				if (!exaccess(file))
				{
					cmd->full_path = file;
					return (0);
				}
				ft_strdel(&file);
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (ht_getfile(paths, cmd));
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
