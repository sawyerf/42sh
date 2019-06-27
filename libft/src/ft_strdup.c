/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 18:40:35 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/16 18:32:07 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

char			*ft_strdup(const char *s1)
{
	char	*copy;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	if (!s1)
		return (NULL);
	if (!(copy = ft_strnew(len)))
		return (0);
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[len] = '\0';
	return (copy);
}
