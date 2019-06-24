/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 18:31:38 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/24 17:10:23 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **tab)
{
	char	**dtab;
	int		count;

	count = 0;
	if (!tab)
	{
		write(1, "lil\n", 4);
		return (ft_tabnew(0));
	}
	if (!(dtab = ft_tabnew(ft_tablen(tab))))
	{
		write(1, "lol\n", 4);
		return (NULL);
	}
	while (tab[count])
	{
		if (!(dtab[count] = ft_strdup(tab[count])))
		{
				write(1, "lel\n", 4);
			ft_tabdel(&dtab);
			return (NULL);
		}
		count++;
	}
	return (dtab);
}
