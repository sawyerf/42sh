/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 18:31:38 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/15 21:45:23 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **tab)
{
	char	**dtab;
	int		count;

	count = 0;
	if (!tab)
		return (ft_tabnew(0));
	if (!(dtab = ft_tabnew(ft_tablen(tab))))
		return (NULL);
	while (tab[count])
	{
		if (!(dtab[count] = ft_strdup(tab[count])))
			return (NULL);
		count++;
	}
	return (dtab);
}
