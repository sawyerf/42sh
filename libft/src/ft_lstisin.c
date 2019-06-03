/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstisin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 20:09:05 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/03 20:14:39 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstisin(t_list *lst, char *is)
{
	while (lst)
	{
		if (!ft_strcmp(lst->content, is))
			return (1);
		lst = lst->next;
	}
	return (0);
}
