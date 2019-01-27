/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 17:01:49 by ktlili            #+#    #+#             */
/*   Updated: 2018/09/18 20:02:30 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t		i;
	int			j;
	char		stop;
	char		*to;
	const char	*from;

	stop = c + '\0';
	to = dst;
	from = src;
	i = 0;
	j = 0;
	while ((i < n) && (j == 0))
	{
		to[i] = from[i];
		if (to[i] == stop)
			return (&to[i + 1]);
		i++;
	}
	return (NULL);
}
