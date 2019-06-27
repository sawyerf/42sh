/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strichr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 15:11:28 by apeyret           #+#    #+#             */
/*   Updated: 2019/01/10 17:55:22 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strichr(char *s, char c, int n)
{
	int count;

	count = 0;
	while (s[count])
	{
		if (s[count] == c)
			break ;
		count++;
	}
	if (n && s[count] == c && s[count])
		return (count + 1);
	return (count);
}
