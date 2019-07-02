/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 19:12:51 by tduval            #+#    #+#             */
/*   Updated: 2019/06/29 05:47:48 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_patmatch.h"
#include "libft.h"

char		*get_beginning(char *lpath, char *dname)
{
	char	*ret;
	char	*tmp;

	if (lpath[ft_strlen(lpath) - 1] != '/')
	{
		if (!(tmp = ft_strjoin(lpath, "/")))
			return (NULL);
	}
	else
	{
		if (!(tmp = ft_strdup(lpath)))
			return (NULL);
	}
	ret = ft_strjoin(tmp, dname);
	ft_strdel(&tmp);
	return (ret);
}

char		*go_last(char *str)
{
	while (str && *str && ft_strchr(str, '/'))
		str++;
	return (str);
}

void		*free_lst(t_lfiles *lst)
{
	if (lst && lst->next)
		free_lst(lst->next);
	if (lst)
	{
		ft_strdel(&(lst->path));
		ft_memdel((void **)&lst);
	}
	return (NULL);
}

char		*go_after(char *str)
{
	int		i;

	i = 0;
	while (str && str[i] && str[i] != '/')
		i++;
	while (str && str[i] && str[i + 1] && str[i + 1] == '/')
		i++;
	return (str && str[i] ? str + i + 1 : NULL);
}

void		*free_all(char *str1, char *str2, char *str3, t_lfiles *lst)
{
	ft_strdel(&str1);
	ft_strdel(&str2);
	ft_strdel(&str3);
	if (lst)
		free_lst(lst);
	return (NULL);
}
