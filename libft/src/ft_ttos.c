/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ttos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:10:27 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/24 16:55:02 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ttos(char **tab, char *sep)
{
	int		i;
	int		len;
	char	*s;

	i = 0;
	len = 0;
	while (tab[i])
	{
		len += ft_strlen(tab[i]);
		i++;
	}
	if (!(s = ft_strnew(len + i)))
		return (NULL);
	i = 0;
	while (tab[i])
	{
		ft_strcat(s, tab[i]);
		i++;
		if (tab[i])
			ft_strcat(s, sep);
	}
	return (s);
}
