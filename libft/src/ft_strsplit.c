/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:55:35 by ktlili            #+#    #+#             */
/*   Updated: 2019/06/25 16:18:48 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_wordcount(char const *s, char c)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

static int		ft_wordlen(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	int		j;
	char	**tab;

	j = 0;
	if (!s)
		return (ft_tabnew(0));
	if (!(tab = ft_tabnew(ft_wordcount(s, c))))
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			if (!(tab[j] = ft_strndup(s, ft_wordlen(s, c))))
			{
				ft_tabdel(&tab);
				return (NULL);
			}
			j++;
			s += ft_wordlen(s, c);
		}
	}
	return (tab);
}
