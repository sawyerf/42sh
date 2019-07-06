/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 20:01:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/05/20 14:17:36 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

void		init_iterator(int *read, int *write)
{
	*read = 0;
	*write = 0;
}

static char	*next_dir(char *path)
{
	int i;

	i = 0;
	while (path[i] == '/')
		i++;
	while ((path[i] != 0) && (path[i] != '/'))
		i++;
	if (path[i] == '/')
		return (&path[i]);
	return (&path[i]);
}

static void	recursive(char *start)
{
	char	*dest;
	char	*src;
	int		len;

	if (!ft_strncmp(start, "../", 3))
		recursive(start + 3);
	else
		return ;
	dest = start;
	if (start[3] == 0)
	{
		*start = 0;
		return ;
	}
	else
		src = next_dir(start + 3);
	len = ft_strlen(src);
	ft_memmove(dest, src, len);
	dest[len] = 0;
}

void		cleandotdot(char *path)
{
	int i;

	ft_strrev(path);
	i = 0;
	if (!ft_strncmp(path, "../", 3))
		recursive(path);
	while (path[i] != 0)
	{
		if (!ft_strncmp(path + i, "/../", 4))
			recursive(&path[i + 1]);
		else
			i++;
	}
	if (*path == 0)
	{
		path[0] = '/';
		path[1] = 0;
	}
	ft_strrev(path);
}

void		cleanpath(char *str)
{
	char	buffer[PATH_MAX];
	int		i;
	int		j;

	init_iterator(&i, &j);
	ft_bzero(buffer, PATH_MAX);
	while (str[i] != 0)
	{
		buffer[j] = str[i];
		j++;
		if (str[i] == '/')
		{
			while ((str[i] == '/') || (!ft_strncmp(str + i, "./", 2))
				|| (!ft_strncmp(str + i, ".", 2)))
			{
				if (!ft_strncmp(str + i, "./", 2))
					i++;
				i++;
			}
		}
		else
			i++;
	}
	ft_bzero(str, ft_strlen(str));
	ft_strcpy(str, buffer);
}
