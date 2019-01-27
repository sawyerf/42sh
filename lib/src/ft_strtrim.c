/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:13:25 by ktlili            #+#    #+#             */
/*   Updated: 2018/07/22 13:52:17 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *s)
{
	int		len;
	int		start;
	int		stop;
	char	*new;

	len = ft_strlen(s);
	start = 0;
	stop = len - 1;
	while (s[start] == 32 || s[start] == '\n' || s[start] == '\t')
		start++;
	if (s[start] == '\0')
	{
		new = ft_strnew(1);
		return (new);
	}
	while (s[stop] == 32 || s[stop] == '\n' || s[stop] == '\t')
		stop--;
	new = ft_strnew(1 + stop - start);
	if (new == NULL)
		return (NULL);
	new = ft_strncpy(new, &s[start], 1 + stop - start);
	return (&new[0]);
}
