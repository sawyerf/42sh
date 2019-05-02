/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 22:05:31 by apeyret           #+#    #+#             */
/*   Updated: 2018/12/24 20:01:36 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabdel(char ***tab)
{
	int count;

	count = 0;
	if (!*tab)
		return ;
	while ((*tab)[count])
	{
		ft_strdel(&((*tab)[count]));
		count++;
	}
	free(*tab);
	*tab = NULL;
}
