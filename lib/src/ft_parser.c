/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 21:42:40 by ktlili            #+#    #+#             */
/*   Updated: 2018/07/17 12:53:46 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	get_flags(const char **input, t_flags *flags)
{
	if (get_level0(input, flags))
		return (0);
	if (get_min_len(input, flags))
		return (0);
	if (get_precision(input, flags))
		return (0);
	if (get_lmod(input, flags))
		return (0);
	if (get_conversion(input, flags) != 1)
		return (-1);
	return (1);
}

int			ft_parser(const char **start, t_flags *flags)
{
	int ret;

	ret = 0;
	flags->precision = -1;
	while (ret == 0)
		ret = get_flags(start, flags);
	if (ret == -1)
		return (-1);
	return (1);
}
