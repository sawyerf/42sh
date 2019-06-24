/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_step.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 19:01:48 by tduval            #+#    #+#             */
/*   Updated: 2019/06/24 22:41:24 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "libft.h"
#include "ft_patmatch.h"

static int	count_width(t_lfiles *lst, char *pattern)
{
	int		i;

	i = 0;
	while (lst)
	{
		if (go_last(lst->path)[0] != '.'
				|| go_last(pattern)[0] == '.')
			i++;
		lst = lst->next;
	}
	return (i);
}

char		**final_step(t_lfiles *lst, int layer, char *pattern)
{
	t_lfiles	*lists[2];
	char		**res;
	struct stat	buf;
	int			i;
	int			f;

	f = pattern[ft_strlen(pattern) - 1] == '/' ? 1 : 0;
	lists[ORIGIN] = lst;
	while (lst && lst->layer != layer)
		lst = lst->next;
	i = count_width(lst, pattern);
	lists[TMP] = lst;
	if (!(res = (char **)ft_memalloc(sizeof(char *) * (i + 2))))
		return (free_lst(lst));
	if (i == 0)
	{
		res[i] = pattern;
		free_lst(lists[ORIGIN]);
		return (res);
	}
	lists[TMP] = lst;
	i = 0;
	while (lists[TMP])
	{
		if (go_last(lists[TMP]->path)[0] != '.'
				|| go_last(pattern)[0] == '.')
		{
			if (f && !(res[i] = ft_strjoin(lists[TMP]->path, "/")))
				return ((char **)free_all(pattern, NULL, NULL, lists[ORIGIN]));
			else
			{
				if (!(res[i] = ft_strdup(lists[TMP]->path)))
					return ((char **)free_all(pattern, NULL, NULL, lists[ORIGIN]));
			}
			i++;
		}
		lists[TMP] = lists[TMP]->next;
	}
	free_lst(lists[ORIGIN]);
	ft_strdel(&pattern);
	return (res);
}
