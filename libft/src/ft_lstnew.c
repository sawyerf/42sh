/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 17:41:38 by ktlili            #+#    #+#             */
/*   Updated: 2019/06/24 19:33:30 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*newlst;

	if (!content)
		return (NULL);
	newlst = malloc(sizeof(t_list));
	if (!newlst || !(newlst->content = ft_strdup(content)))
	{
		free(newlst);
		return (NULL);
	}
	newlst->content_size = content_size;
	newlst->next = NULL;
	newlst->prev = NULL;
	return (newlst);
}
