/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:54:56 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/10 18:45:30 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		rplcount(char *str, char *to)
{
	int		len;
	int		i;
	char	*tmp;

	i = 0;
	tmp = str;
	len = ft_strlen(to);
	while ((tmp = ft_strstr(tmp, to)))
	{
		tmp += len;
		i++;
	}
	return (i);
}

static int		rpllen(char *str, char *to, char *by)
{
	int lento;
	int lenby;
	int	lenstr;
	int word;

	lento = ft_strlen(to);
	lenby = ft_strlen(by);
	lenstr = ft_strlen(str);
	word = rplcount(str, to);
	return (lenstr - (lento * word) + (lenby * word));
}

int				ft_strnext(char *str, char *to)
{
	char *tmp;

	if (!(tmp = ft_strstr(str, to)))
		return (ft_strlen(str));
	return (tmp - str);
}

static char		*strstrcpy(char *dst, char *src, char *to, char *by)
{
	char	*tmp;
	int		lento;
	int		lenby;
	int		next;

	lento = ft_strlen(to);
	lenby = ft_strlen(by);
	tmp = dst;
	while (*src)
	{
		next = ft_strnext(src, to);
		ft_strncpy(tmp, src, next);
		tmp += next;
		src += next;
		if (*src)
		{
			src += lento;
			ft_strcpy(tmp, by);
			tmp += lenby;
		}
	}
	return (dst);
}

char			*ft_replace(char *str, char *to, char *by)
{
	int		len;
	char	*dst;

	len = rpllen(str, to, by);
	if (!(dst = ft_strnew(len)))
		return (NULL);
	return (strstrcpy(dst, str, to, by));
}
