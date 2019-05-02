/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 19:32:33 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/12 18:58:26 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*to;
	char		*buffer;
	const char	*from;

	to = dst;
	from = src;
	buffer = (char *)malloc(sizeof(char) * (len));
	ft_memcpy(buffer, from, len);
	ft_memcpy(to, buffer, len);
	free(buffer);
	return (dst);
}
