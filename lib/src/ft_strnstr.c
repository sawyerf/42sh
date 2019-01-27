/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:56:59 by ktlili            #+#    #+#             */
/*   Updated: 2018/07/22 13:52:17 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <string.h>

char			*ft_strnstr(const char *haystack,
		const char *needle, size_t len)
{
	size_t	i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = ft_strlen(needle);
	if (count == 0)
		return ((char*)haystack);
	while ((haystack[i] != 0) & (i < len))
	{
		while (haystack[i] == needle[j] && j < count && i < len)
		{
			i++;
			j++;
		}
		if (j == count)
			return ((char*)&haystack[i - j]);
		else
			i = i - j;
		j = 0;
		i++;
	}
	return (NULL);
}
