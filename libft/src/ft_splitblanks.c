/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitblanks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 23:38:40 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/12 18:58:26 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isblank(char c)
{
	if ((c == ' ') || (c == '\t') || (c == '\r'))
		return (1);
	return (0);
}

static int	ft_wordcount(char const *s)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isblank(s[i]))
			i++;
		else
		{
			count++;
			while ((!ft_isblank(s[i])) && (s[i] != '\0'))
				i++;
		}
	}
	return (count);
}

static int	ft_wordlen(char const *s)
{
	int i;

	i = 0;
	while ((!ft_isblank(s[i])) && (s[i] != '\0'))
		i++;
	return (i);
}

static void	init_index(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

char		**ft_splitblanks(char const *s)
{
	int		i;
	int		j;
	int		wordlen;
	char	**tab;

	init_index(&i, &j);
	if ((tab = malloc(sizeof(char*) * (ft_wordcount(s) + 1))) == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (ft_isblank(s[i]))
			i++;
		else
		{
			wordlen = ft_wordlen(&s[i]);
			if ((tab[j] = (char *)malloc(1 + (sizeof(char) * wordlen))) == NULL)
				return (NULL);
			tab[j][wordlen] = 0;
			ft_strncpy(tab[j], &s[i], wordlen);
			j++;
			i = i + wordlen;
		}
	}
	tab[j] = 0;
	return (tab);
}
