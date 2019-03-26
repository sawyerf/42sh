/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:54:56 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/26 15:29:23 by apeyret          ###   ########.fr       */
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

static int		lennext(char *str, char *to)
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
		next = lennext(src, to);
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

char	*ft_replace(char *str, char *to, char *by)
{
	int		len;
	char	*dst;

	len = rpllen(str, to, by);
	strstrcpy(dst, str, to, by);
	if (!(dst = ft_strnew(len)))
		return (NULL);
	return (strstrcpy(dst, str, to, by));
}
int main(int ac, char **av)
{
	(void)ac;
	ft_printf("%s\n", ft_replace(av[1], av[2], av[3]));
}
