/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_matches.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:02:05 by tduval            #+#    #+#             */
/*   Updated: 2019/07/08 13:29:07 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <dirent.h>
#include "libft.h"
#include "ft_patmatch.h"
#include "sh_core.h"

static char		*get_current_pattern(char *pattern)
{
	int		i;

	i = 0;
	while (pattern && pattern[i] && pattern[i] != '/')
		i++;
	return (ft_strsub(pattern, 0, i));
}

t_lfiles		*init_list(char *path, int layer)
{
	t_lfiles	*res;

	if (!(res = (t_lfiles *)ft_memalloc(sizeof(t_lfiles))))
		return (NULL);
	res->layer = layer;
	if (layer == -1)
	{
		if (path[0] == '/')
			res->path = ft_strdup("/");
		else
			res->path = ft_strdup("./");
	}
	else
		res->path = path;
	res->next = NULL;
	return (res);
}

static t_lfiles	*get_files(t_lfiles *lst, char *pattern, int i)
{
	t_lfiles		*lists[2];
	char			*str[4];

	str[PATTERN] = pattern;
	lists[TMP_LST] = lst;
	if (!(str[CURPATTERN] = get_current_pattern(str[PATTERN])))
		return (NULL);
	while ((!g_sh.interrupt) && (lists[TMP_LST] && lists[TMP_LST]->next
			&& lists[TMP_LST]->layer != i - 1))
		lists[TMP_LST] = lists[TMP_LST]->next;
	while (lists[TMP_LST] && lists[TMP_LST]->layer == i - 1)
	{
		if (!(read_curdir(str, lists, i)))
			return (0);
		lists[TMP_LST] = lists[TMP_LST]->next;
	}
	free(str[CURPATTERN]);
	return (lst);
}

char			**ret_matches(char *pattern)
{
	t_lfiles		*lst;
	char			*origin;
	int				layer;
	int				i;

	i = 0;
	if (!(origin = ft_strdup(pattern)))
		return (NULL);
	pattern = format_pattern(pattern);
	if (!(lst = init_list(pattern, -1)))
		return ((char **)free_all(origin, NULL, NULL, NULL));
	if (pattern[0] == '/')
		while (pattern && *pattern && *pattern == '/')
			pattern++;
	layer = get_layer(pattern);
	while (i <= layer && lst)
	{
		if (!(lst = get_files(lst, pattern, i)))
			return (NULL);
		pattern = go_after(pattern);
		i++;
	}
	return (final_step(lst, layer, origin));
}
