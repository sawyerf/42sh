/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:40:06 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/12 18:58:26 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst)
{
	t_list	*temp;

	if (!*alst)
		return ;
	while ((*alst)->next)
	{
		temp = (*alst)->next;
		free((*alst)->content);
		(*alst)->content = 0;
		free(*alst);
		*alst = NULL;
		*alst = temp;
	}
	free((*alst)->content);
	free(*alst);
	*alst = NULL;
}
