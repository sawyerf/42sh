/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:28:51 by apeyret           #+#    #+#             */
/*   Updated: 2018/12/26 21:19:07 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dst, const char *src)
{
	int	count;

	count = 0;
	if (!dst || !src)
		return (dst);
	while (src[count])
	{
		dst[count] = src[count];
		count++;
	}
	dst[count] = '\0';
	return (dst);
}
