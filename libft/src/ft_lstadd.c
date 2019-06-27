/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 18:48:23 by ktlili            #+#    #+#             */
/*   Updated: 2019/06/27 19:55:09 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstadd(t_list **alst, t_list *new)
{
	t_list *tmp;

	if (!new || !alst)
		return (0);
	tmp = new;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = *alst;
	if (*alst)
		(*alst)->prev = tmp;
	*alst = new;
	new->prev = NULL;
	return (0);
}
