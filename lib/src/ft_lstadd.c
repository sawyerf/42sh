/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:48:23 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/21 16:36:43 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	t_list *tmp;

	if (!new)
		return;
	if (!alst)
		return ;
	tmp = new;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = *alst;
	if (*alst)
		(*alst)->prev = tmp;
	*alst = new;
	new->prev = NULL;
}
