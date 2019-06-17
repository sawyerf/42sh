/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   folderin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:13:43 by tduval            #+#    #+#             */
/*   Updated: 2019/06/17 16:14:09 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_list	*folderin(DIR *ptr, char *path, char *exec, int (*f)(char *file))
{
	struct dirent	*ret;
	t_list			*lst;
	char			*cpath;
	int				len;
	int				count;

	count = 0;
	lst = NULL;
	len = ft_strlen(exec);
	while ((ret = readdir(ptr)))
	{
		if (!(cpath = ft_zprintf("%s/%s", path, ret->d_name)))
			continue ;
		if (!f(cpath) && !ft_strncmp(ret->d_name, exec, ft_strlen(exec))
				&& ft_strcmp(ret->d_name, "..") && ft_strcmp(ret->d_name, "."))
		{
			ft_lstadd(&lst, ft_lstnew(ret->d_name + len, exaccess(cpath)));
			count++;
		}
		ft_strdel(&cpath);
	}
	return (lst);
}
