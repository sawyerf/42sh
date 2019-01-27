/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:45:57 by ktlili            #+#    #+#             */
/*   Updated: 2018/07/22 13:52:17 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <string.h>

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_total;
	size_t	i;

	i = 0;
	len_dst = ft_strlen(dst);
	if (len_dst > size)
		len_dst = size;
	len_total = len_dst + ft_strlen(src);
	while (len_dst < size && src[i] != '\0')
	{
		dst[len_dst] = src[i];
		len_dst++;
		i++;
	}
	if (len_dst == size)
		len_dst--;
	if (i != 0)
		dst[len_dst] = '\0';
	return (len_total);
}
