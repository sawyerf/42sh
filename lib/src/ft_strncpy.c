/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:32:26 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/25 15:06:23 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	int	count;

	count = 0;
	if (!dst || !src)
		return (dst);
	while (src[count] && count < (int)len)
	{
		dst[count] = src[count];
		count++;
	}
	while (count < (int)len)
	{
		dst[count] = '\0';
		count++;
	}
	dst[count + 1] = 0;
	return (dst);
}
