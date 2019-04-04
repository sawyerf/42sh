/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:31:07 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/04 14:00:03 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "hashtable.h"

void	hash_init(t_hash *hash)
{
	hash->opt[0] = 0;
	hash->opt[1] = 0;
	hash->search = NULL;
}

int		hash_parser(char **av, t_hash *hash)
{
	av++;
	hash_init(hash);
	while (*av)
	{
		if (!ft_strcmp(*av, "--") || **av != '-')
		{
			if (!(ft_strcmp("--", *av)))
				av++;
			break ;
		}
		if (!parser_takeopt("r", *av, hash->opt, "hash"))
			return (-1);
		av++;
	}
	hash->search = av;
	return (0);
}

int		hash_print(t_list **hst)
{
	t_list	*lst;
	int		i;

	i = 0;
	lst = NULL;
	ft_printf("keys    command\n");
	while (i < HT_SIZE)
	{
		if ((lst = hst[i]))
		{
			while (lst)
			{
				ft_printf("%-4d    %s\n", i, lst->content);
				lst = lst->next;
			}
		}
		i++;
	}
	return (0);
}

int		getsplitpath(char ***paths)
{
	char	*path;

	if (!(path = get_env_value("PATH")))
	{
		ft_printf("fc: PATH not set\n");
		*paths = NULL;
		return (1);
	}
	if (!(*paths = ft_strsplit(path, ':')))
		return (MEMERR);
	return (0);
}

int		hash(t_cmd_tab *cmd)
{
	t_list	**hst;
	char	**paths;
	t_hash	hash;

	paths = NULL;
	if (hash_parser(cmd->av, &hash))
		return (1);
	if (ft_cisin(hash.opt, 'r') || *hash.search)
	{
		if (ft_cisin(hash.opt, 'r'))
			ht_del();
		if (getsplitpath(&paths) == MEMERR)
			return (MEMERR);
		while (paths && *hash.search)
		{
			if (!ht_getpath(paths, *hash.search))
				ht_addfile(paths, *hash.search);
			hash.search++;
		}
		ft_tabdel(&paths);
		return (0);
	}
	hst = ht_gget();
	hash_print(hst);
	return (0);
}
