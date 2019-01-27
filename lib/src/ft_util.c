/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 19:48:26 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/05 19:23:36 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	str_upper(char *str)
{
	while (*str)
	{
		*str = ft_toupper(*str);
		str++;
	}
}

int		get_base(t_conversion conversion)
{
	if ((conversion == d) || (conversion == D)
			|| (conversion == u) || (conversion == U) || (conversion == i))
		return (10);
	else if ((conversion == o) || (conversion == O))
		return (8);
	else if ((conversion == x) || (conversion == X) || (conversion == p))
		return (16);
	return (10);
}

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

char	select_padding(t_flags flags)
{
	char padding;

	padding = ' ';
	if ((!flags.left_adj) && (flags.zero_pad))
		padding = '0';
	return (padding);
}
