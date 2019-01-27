/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 19:11:18 by ktlili            #+#    #+#             */
/*   Updated: 2018/07/17 11:04:00 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include <string.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	int		flag;

	i = 0;
	flag = 0;
	while (i < len)
	{
		if ((flag == 1) || (src[i] == '\0'))
		{
			flag = 1;
			dst[i] = '\0';
			i++;
		}
		else
		{
			dst[i] = src[i];
			i++;
		}
	}
	return (&dst[0]);
}
