/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 14:40:53 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/20 18:48:59 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "ft_eval.h"

t_list *g_thash[HT_SIZE];

t_list **ht_gget(void)
{
	return (g_thash);
}

void	ht_del(void)
{
	int count;

	count = 0;
	while (count < HT_SIZE)
	{
		if (g_thash[count])
			ft_lstdel(&g_thash[count]);
		g_thash[count] = NULL;
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

char	*ht_getpath(char **paths, char *exec)
{
	t_list	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ht_get(paths[i]);
		while (tmp)
		{
			//ft_printf("hash: %s | %s\n", tmp->content, tmp->content + tmp->content_size);
			if (!ft_strcmp(exec, tmp->content + tmp->content_size))
			{
				if (!exaccess(tmp->content))
				{
					free_tab(paths);
					return (tmp->content);
				}
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

	if (!(paths = ft_strsplit(path, ':')))
		return (MEMERR);
	if ((result = ht_getpath(paths, cmd->av[0])))
	{
		if (!(cmd->full_path = ft_strdup(result)))
			return (MEMERR);
		return (0);
	}
	return (ht_getfile(paths, cmd));
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
