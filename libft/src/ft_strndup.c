/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:18:09 by apeyret           #+#    #+#             */
/*   Updated: 2018/11/30 14:30:48 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int size)
{
	int		count;
	int		len;
	char	*str;

	len = 0;
	count = 0;
	len = ft_strlen(s);
	if (size < len)
		str = ft_strnew(size);
	else
		str = ft_strnew(len);
	while (s[count] && count < size)
	{
		str[count] = s[count];
		count++;
	}
	str[count] = '\0';
	return (str);
}
