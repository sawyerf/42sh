/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 22:27:00 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/12 22:35:17 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sh_core.h"

static char	*test_access(char *path, char *binname, int *ret)
{
	char *tmp;

	tmp = ft_strjoin(path, binname);
	if (tmp == NULL)
		return (NULL);
	if ((ret[0] = bin_perm(tmp)) == 0)
		return (tmp);
	else if (ret[0] != 4)
		ret[1] = ret[0];
	free(tmp);
	return (NULL);
}

static char	*iter_paths(char **tab, char *binname, int *ret)
{
	char	*tmp;
	int		i;

	i = 0;
	while (tab[i] != NULL)
	{
		add_slash(&tab[i]);
		if ((tmp = test_access(tab[i], binname, ret)) != NULL)
		{
			free_tab(tab);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

char		*searchbin(char *binname, char *path)
{
	char	**tab;
	char	*tmp;
	int		ret[2];

	tab = NULL;
	ret[1] = 2;
	if (path != NULL)
		if ((tab = ft_strsplit(path, ':')) == NULL)
			return (NULL);
	if ((path == NULL) || (tab[0] == NULL))
	{
		if (bin_perm(binname) == 0)
		{
			if (tab != NULL)
				free_tab(tab);
			return (ft_strdup(binname));
		}
	}
	else if ((tmp = iter_paths(tab, binname, ret)) != NULL)
		return (tmp);
	exec_error(ret[1], binname);
	if (tab != NULL)
		free_tab(tab);
	return (NULL);
}
