/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 16:10:23 by ktlili            #+#    #+#             */
/*   Updated: 2019/05/27 16:45:53 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

int			add_slash(char **path)
{
	int		len;
	char	*tmp;

	len = ft_strlen(*path);
	if ((len != 0) && ((*path)[len - 1] != '/'))
	{
		if (!(tmp = ft_strjoin(*path, "/")))
			return (MEMERR);
		ft_strdel(path);
		*path = tmp;
	}
	return (0);
}

int			ft_cmptab(char **tab, char *str)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		if (!ft_strcmp(tab[i], str))
			return (i);
		i++;
	}
	return (-1);
}
