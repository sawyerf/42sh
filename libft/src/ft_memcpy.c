/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 16:09:21 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/12 18:58:26 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*to;
	const char	*from;

	to = dst;
	from = src;
	i = 0;
	while (i < n)
	{
		to[i] = from[i];
		i++;
	}
	return (dst);
}
