/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 16:10:23 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/28 14:16:54 by ktlili           ###   ########.fr       */
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
		tmp = ft_strjoin(*path, "/");
		if (tmp == NULL)
			return (MEMERR);
		free(*path);
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

char		**dup_tab(char **tab)
{
	size_t	len;
	size_t	i;
	char	**copy;

	len = 0;
	i = 0;
	while (tab[len] != NULL)
		len++;
	copy = malloc((len + 1) * sizeof(char*));
	if (copy == NULL)
		return (NULL);
	while (i < len)
	{
		copy[i] = ft_strdup(tab[i]);
		if (copy[i] == NULL)
		{
			free_tab(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
