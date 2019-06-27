/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:18:09 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/24 18:12:05 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int size)
{
	int		count;
	int		len;
	char	*str;

	if (!s)
		return (NULL);
	len = 0;
	count = 0;
	len = ft_strlen(s);
	if (size < len)
		str = ft_strnew(size);
	else
		str = ft_strnew(len);
	if (!str)
		return (NULL);
	while (s[count] && count < size)
	{
		str[count] = s[count];
		count++;
	}
	str[count] = '\0';
	return (str);
}
