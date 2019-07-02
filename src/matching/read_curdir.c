/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_curdir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 06:24:46 by tduval            #+#    #+#             */
/*   Updated: 2019/06/29 06:42:21 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <dirent.h>
#include "ft_patmatch.h"
#include "libft.h"

static int		slash_case(t_lfiles *lists[2], char *str[4],
		struct dirent *files, int i)
{
	char		*tmp;
	struct stat	buf;

	if ((!(str[TMP1] = ft_strjoin(lists[TMP_LST]->path, "/")))
			|| !(str[TMP2] = ft_strjoin(str[TMP1], files->d_name)))
		return ((int)free_all(str[TMP1], NULL, NULL, NULL));
	if (stat(str[TMP2], &buf) != -1 && S_ISDIR(buf.st_mode))
	{
		if (!(tmp = get_beginning(lists[TMP_LST]->path, files->d_name))
			|| !(lists[SUBTMP_LST]->next = init_list(ft_strjoin(tmp, "/"), i)))
			return ((int)free_all(str[0], str[1], tmp, NULL));
		ft_strdel(&tmp);
		lists[SUBTMP_LST] = lists[SUBTMP_LST]->next;
	}
	free_all(str[TMP1], str[TMP2], NULL, NULL);
	return (1);
}

static int		append_file(t_lfiles *lists[2], char *str[4],
		struct dirent *files, int i)
{
	if (str[PATTERN][ft_strlen(str[PATTERN]) - 1] == '/')
	{
		if (!(slash_case(lists, str, files, i)))
			return (0);
	}
	else
	{
		if (!(lists[SUBTMP_LST]->next = init_list(
						get_beginning(lists[TMP_LST]->path, files->d_name), i)))
			return ((int)free_all(str[0], str[1], str[2], NULL));
		lists[SUBTMP_LST] = lists[SUBTMP_LST]->next;
	}
	return (1);
}

static int		check_all(struct dirent *files, char *str[4],
		t_lfiles *lists[2], int i)
{
	if (matches(files->d_name, str[CURPATTERN], 0)
			&& (ft_strcmp(files->d_name, "..") || str[CURPATTERN][0] == '.')
			&& (ft_strcmp(files->d_name, ".") || str[CURPATTERN][0] == '.')
			&& (files->d_name[0] != '.' || str[CURPATTERN][0] == '.'))
	{
		if (!(append_file(lists, str, files, i)))
			return (0);
		else
			return (1);
	}
	else
		return (1);
}

int				read_curdir(char *str[4], t_lfiles *lists[2], int i)
{
	DIR				*dir;
	struct dirent	*files;

	if ((dir = opendir(lists[TMP_LST]->path)) != NULL)
	{
		lists[SUBTMP_LST] = lists[TMP_LST];
		while (lists[SUBTMP_LST] && lists[SUBTMP_LST]->next)
			lists[SUBTMP_LST] = lists[SUBTMP_LST]->next;
		while ((files = readdir(dir)) != NULL)
		{
			if (check_all(files, str, lists, i) == 0)
			{
				closedir(dir);
				return (0);
			}
		}
		closedir(dir);
	}
	return (1);
}
