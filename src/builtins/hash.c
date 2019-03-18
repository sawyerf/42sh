/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:31:07 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/18 12:48:54 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"

void	hash_init(t_hash *hash)
{
	hash->opt[0] = 0;
	hash->opt[1] = 0;
	hash->search = NULL;
}

void	hash_parser(char **av, t_hash *hash)
{
	int	i;

	while (*av)
	{
		if (!ft_strcmp(*av, "--") || **av != '-')
		{
			if (!(ft_strcmp("--", *av)))
				av++;
			break ;
		}
		i = 1;
		while ((*av)[i])
		{
			if (!ft_cisin(hash->opt, (*av)[i]))
			{
				if (ft_cisin("r", (*av)[i]))
					ft_strncat(hash->opt, *av + i, 1);
				else
					ft_dprintf(2, "usage: hash [-r] [name ...]\n");
			}
			i++;
		}
		av++;
	}
	hash->search = av;
}

int		hash_print(t_list **hst)
{
	t_list *lst;
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

int		hash(t_cmd_tab *cmd)
{
	t_list	**hst;
	char	*path;
	t_hash	hash;

	hash_parser(cmd->av, &hash);
	if (ft_cisin(hash.opt, 'r'))
	{
		if (ft_cisin(hash.opt, 'r'))
			ht_del();
		path = get_env_value("PATH");
		while (*hash.search)
		{
			//hstadd();
			hash.search++;
		}
	}
	else
	{
		hst = ht_gget();
		hash_print(hst);
	}
	return (0);
}
