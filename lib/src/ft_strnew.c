/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 13:42:56 by ktlili            #+#    #+#             */
/*   Updated: 2018/09/09 22:53:29 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_strnew(size_t size)
{
	char	*p;
	size_t	i;

	i = 0;
	p = (char*)malloc(size + 1);
	if (p == NULL)
		return (NULL);
	while (i <= size)
	{
		p[i] = 0;
		i++;
	}
	return (p);
}
