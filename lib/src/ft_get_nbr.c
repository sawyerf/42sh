/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_nbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:46:48 by ktlili            #+#    #+#             */
/*   Updated: 2018/07/17 12:53:20 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	get_signed(t_flags flags, char *buffer, va_list ap)
{
	intmax_t	store;
	int			wrote;
	int			base;

	store = 0;
	wrote = 0;
	if (flags.length_mod == hh)
		store = (char)va_arg(ap, int);
	else if (flags.length_mod == h)
		store = (short)va_arg(ap, int);
	else if (flags.length_mod == none)
		store = (intmax_t)va_arg(ap, int);
	else if (flags.length_mod == l)
		store = (intmax_t)va_arg(ap, long);
	else if (flags.length_mod == ll)
		store = (intmax_t)va_arg(ap, long long);
	else if (flags.length_mod == j)
		store = (intmax_t)va_arg(ap, intmax_t);
	else if (flags.length_mod == z)
		store = (intmax_t)va_arg(ap, size_t);
	base = get_base(flags.conversion);
	if ((store == 0) && (flags.precision == 0))
		return (0);
	wrote = ft_itoa_base(store, base, buffer, 1);
	return (wrote);
}

int	get_unsigned(t_flags *flags, char *buffer, va_list ap)
{
	uintmax_t	store;
	int			wrote;

	store = 0;
	if (flags->length_mod == hh)
		store = (unsigned char)va_arg(ap, unsigned int);
	else if (flags->length_mod == h)
		store = (unsigned short)va_arg(ap, unsigned int);
	else if (flags->length_mod == none)
		store = va_arg(ap, unsigned int);
	else if (flags->length_mod == l)
		store = va_arg(ap, unsigned long);
	else if (flags->length_mod == ll)
		store = va_arg(ap, unsigned long long);
	else if (flags->length_mod == j)
		store = va_arg(ap, uintmax_t);
	else if (flags->length_mod == z)
		store = va_arg(ap, size_t);
	if ((store == 0) && (flags->conversion != p) && (flags->conversion != o))
		flags->alt_form = 0;
	if ((store == 0) && (flags->precision == 0))
		return (0);
	wrote = ft_utoa_base(store, get_base(flags->conversion), buffer, 1);
	return (wrote);
}
