/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:31:07 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/06 21:00:05 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"

int		hash_print(t_list **hst)
{
	t_list *lst;
	int		i;

	i = 0;
	lst = NULL;
	ft_printf("hits    command\n");
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

	(void)cmd;
	hst = ht_gget();
	hash_print(hst);
	return (0);
}
