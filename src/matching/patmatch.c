/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patmatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 00:38:56 by tduval            #+#    #+#             */
/*   Updated: 2019/06/14 01:23:16 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	**init_res(char *pattern)
{
	int	c;

	c = 0;
	while (
}

static char	*get_pattern(char *str)
{
	char	*res;
	char	*tmp;

	if (str[0] == '/')
		return (str);
	else
	{
		tmp = ft_strjoin(ft_getenv(env, "PWD"), "/");
		res = ft_strjoin(tmp, str);
		ft_strdel(&tmp);
		return (res);
	}
}

char		**patmatch(char *str)
{
	char	*pattern;
	char	**res;

	if (!(pattern = get_pattern(str)))
		return (NULL);
	res = init_res(pattern);
	if (res)
		res = get_matches(pattern);
	return (res);
}
