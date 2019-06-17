/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acp_multicpl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 18:46:37 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/17 15:57:59 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		iscolst(t_list *lst, char c, size_t i)
{
	while (lst)
	{
		if (!(ft_strlen(lst->content) > i))
			return (0);
		if (((char*)lst->content)[i] != c)
			return (0);
		lst = lst->next;
	}
	return (1);
}

int		acp_multichc(t_rdl *rdl, t_list *lst)
{
	char	*s;
	int		i;

	i = 0;
	s = lst->content;
	while (*s)
	{
		if (!iscolst(lst, *s, i))
			break ;
		rdladd(rdl, *s);
		s++;
		i++;
	}
	if (i)
		return (1);
	return (0);
}
