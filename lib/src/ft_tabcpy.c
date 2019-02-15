/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 23:41:08 by apeyret           #+#    #+#             */
/*   Updated: 2019/01/15 16:37:14 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ms_tabcpy(char **dst, char **cpy)
{
	int		count;

	count = 0;
	if (!cpy || !dst)
		return (dst);
	while (cpy[count])
	{
		dst[count] = cpy[count];
		count++;
	}
	dst[count] = NULL;
	return (dst);
}
