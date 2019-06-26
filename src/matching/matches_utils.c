/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matches_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 18:34:23 by tduval            #+#    #+#             */
/*   Updated: 2019/06/26 04:31:16 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_patmatch.h"

char	*ft_strapp(char *str, char c)
{
	char	*res;
	int		i;

	i = 0;
	if (!(res = ft_memalloc(sizeof(char *) * (ft_strlen(str) + 1))))
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	ft_strdel(&str);
	res[i] = c;
	return (res);
}

int	is_in_str(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int	is_last(char *str)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (str[i])
	{
		if (str[i] == ']')
			return (0);
		if (str[i] == '[')
			return (1);
		i++;
	}
	return (1);
}

char	*after_bracket(char *str)
{
	while (str && *str)
	{
		if (*str == ']' && is_last(str))
			break ;
		str++;
	}
	return (*str ? str : NULL);
}

char	*get_chars(char *str, char c1, char c2)
{
	while (c1 <= c2)
	{
		str = ft_strapp(str, c1);
		c1++;
	}
	return (str);
}
