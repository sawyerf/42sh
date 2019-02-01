/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 22:18:46 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/01 14:08:46 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

int	ft_ispath(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}

int	path_access(char *path)
{
	struct stat target_data;

	if (stat(path, &target_data) != 0)
		return (2);
	if (!S_ISDIR(target_data.st_mode))
		return (5);
	if (access(path, X_OK) != 0)
		return (3);
	return (0);
}

int	dir_access(char *cd_path, char **curpath)
{
	struct stat	target_data;
	char		*tmp_path;

	tmp_path = ft_strjoin(cd_path, *curpath);
	if (tmp_path == NULL)
		return (MEMERR);
	if (stat(tmp_path, &target_data) != 0)
	{
		free(tmp_path);
		return (-1);
	}
	if ((S_ISDIR(target_data.st_mode)) && (!access(tmp_path, X_OK)))
	{
		free(*curpath);
		*curpath = tmp_path;
		return (0);
	}
	free(tmp_path);
	return (-1);
}
