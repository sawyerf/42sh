/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:55:35 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/10 18:44:07 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_sep(char c, char *sep)
{
	while (*sep)
	{
		if (*sep == c)
			return (1);
		sep++;
	}
	return (0);
}

static int		ft_wordcount(char const *s, char *sep)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_is_sep(s[i], sep))
			i++;
		else
		{
			count++;
			while ((!ft_is_sep(s[i], sep) && s[i] != '\0'))
				i++;
		}
	}
	return (count);
}

static int		ft_wordlen(char const *s, char *sep)
{
	int i;

	i = 0;
	while (!ft_is_sep(s[i], sep) && s[i] != '\0')
		i++;
	return (i);
}

static	void	init_index(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

char			**ft_strnsplit(char const *s, char *sep)
{
	int		i;
	int		j;
	int		wordlen;
	char	**tab;

	init_index(&i, &j);
	if ((tab = malloc(sizeof(char*) * (ft_wordcount(s, sep) + 1))) == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (ft_is_sep(s[i], sep))
			i++;
		else
		{
			wordlen = ft_wordlen(&s[i], sep);
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
