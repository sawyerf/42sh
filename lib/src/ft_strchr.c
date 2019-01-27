/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 20:09:49 by ktlili            #+#    #+#             */
/*   Updated: 2018/07/22 13:52:17 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <string.h>

char			*ft_strchr(const char *s, int c)
{
	char		target;
	int			i;
	int			len;

	len = ft_strlen(s);
	target = c;
	i = 0;
	while (i <= len)
	{
		if (s[i] == target)
			return ((char*)&s[i]);
		i++;
	}
	return (NULL);
}
