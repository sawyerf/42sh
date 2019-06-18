/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matches.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 16:29:08 by tduval            #+#    #+#             */
/*   Updated: 2019/06/18 22:02:55 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_patmatch.h"
#include "libft.h"

static char	*perform_it(char *s1, char *s2, char *arr, int i)
{
	if (i && s2[i] == '-' && s2[i + 1] != ']')
		arr = get_chars(arr, s2[i - 1], s2[i + 1]);
	else
	{
		if (s2[i - 1] != '-' && s2[i + 1] != '-')
		{
			if (!(arr = ft_strapp(arr, s2[i])))
				return (NULL);
		}
	}
	return (arr);
}

static char	*range(char *s1, char *s2)
{
	char	*arr;
	int		i;
	int		n;

	if (*s2 == '!')
	{
		s2++;
		n = 1;
	}
	else
		n = 0;
	i = 0;
	if (!(arr = ft_strnew(0)))
		return (0);
	while (s2[i] && after_bracket(s2) != s2 + i)
	{
		arr = perform_it(s1, s2, arr, i);
		i++;
	}
	if ((is_in_str(arr, *s1) && n == 0) || (!is_in_str(arr, *s1) && n))
	{
		ft_strdel(&arr);
		return (after_bracket(s2) + 1);
	}
	ft_strdel(&arr);
	return (NULL);
}

int			matches(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	if (*s2 == '[' && ft_strchr(s2, ']') && *s1 != '\0')
		return (matches(s1 + 1, range(s1, s2 + 1)));
	if (*s2 == '?' && *s1 != '\0')
		return (matches(s1 + 1, s2 + 1));
	if (*s2 == '*' && *s1 != '\0')
		return (matches(s1 + 1, s2) || matches(s1, s2 + 1));
	if (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
		return (matches(s1 + 1, s2 + 1));
	if (*s1 == *s2 && *s1 == '\0' && *s2 == '\0')
		return (1);
	if (*s2 == '*' && *s1 == '\0' && *(s2 + 1) == '\0')
		return (1);
	return (0);
}
