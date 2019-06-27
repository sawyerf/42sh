/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 19:17:08 by apeyret           #+#    #+#             */
/*   Updated: 2018/12/21 19:39:24 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabnew(size_t size)
{
	char	**tab;
	size_t	count;

	count = 0;
	if (!(tab = (char**)malloc(sizeof(char**) * (size + 1))))
		return (NULL);
	while (count < size + 1)
	{
		tab[count] = NULL;
		count++;
	}
	return (tab);
}
