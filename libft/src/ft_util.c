/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 19:48:26 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/12 18:58:26 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_char_cmp(char chr, char *array)
{
	int i;

	i = 0;
	while (array[i])
	{
		if (chr == array[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_swap_char(char *a, char *b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}
