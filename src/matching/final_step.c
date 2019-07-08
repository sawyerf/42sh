/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_step.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 19:01:48 by tduval            #+#    #+#             */
/*   Updated: 2019/07/08 15:36:17 by apeyret          ###   ########.fr       */
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

char		*remove_bs(char *pattern)
{
	int		i;

	i = 0;
	while (pattern[i])
	{
//		if (pattern[i] == '\\')
//			ft_strremoveat(pattern, i);
//		if (pattern[i])
		i++;
	}
	return (pattern);
}

char		*fill_tab(t_lfiles *lists[2], char *pattern)
{
	char	*res;

	if (ft_strnequ(pattern, "../", 3)
			|| ft_strnequ(pattern, "./", 2)
			|| ft_strnequ(pattern, "/", 1))
	{
		if (!(res = ft_strdup(lists[TMP]->path)))
			return ((char *)
					free_all(pattern, NULL, NULL, lists[ORIGIN]));
	}
	else
	{
		lists[TMP]->path = ft_strremoveat(lists[TMP]->path, 0);
		lists[TMP]->path = ft_strremoveat(lists[TMP]->path, 0);
		if (!(res = ft_strdup(lists[TMP]->path)))
			return ((char *)
					free_all(pattern, NULL, NULL, lists[ORIGIN]));
	}
	return (res);
}

char		**end_game(char **res, t_lfiles *lists[2], char *pattern, int i)
{
	if (i == 0)
	{
		res[i] = remove_bs(pattern);
		free_lst(lists[ORIGIN]);
		return (res);
	}
	i = 0;
	while (lists[TMP])
	{
		if (go_last(lists[TMP]->path)[0] != '.'
				|| go_last(pattern)[0] == '.')
		{
			if (!(res[i] = fill_tab(lists, pattern)))
				return (NULL);
			i++;
		}
		lists[TMP] = lists[TMP]->next;
	}
	free_lst(lists[ORIGIN]);
	ft_strdel(&pattern);
	return (res);
}

char		**final_step(t_lfiles *lst, int layer, char *pattern)
{
	t_lfiles	*lists[2];
	char		**res;
	int			i;
	int			f;

	if (ft_strlen(pattern) > 1)
		f = pattern[ft_strlen(pattern) - 1] == '/' ? 1 : 0;
	else
		f = pattern[0] == '/' ? 1 : 0;
	lists[ORIGIN] = lst;
	while (lst && lst->layer != layer)
		lst = lst->next;
	i = count_width(lst, pattern);
	lists[TMP] = lst;
	if (!(res = (char **)ft_memalloc(sizeof(char *) * (i + 2))))
		return (free_lst(lst));
	lists[TMP] = lst;
	return (end_game(res, lists, pattern, i));
}
