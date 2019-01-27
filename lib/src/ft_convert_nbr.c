/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 16:55:10 by ktlili            #+#    #+#             */
/*   Updated: 2018/07/17 12:51:08 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int		ft_field_width(t_flags flags, int size, char prefix[3])
{
	int		to_write;
	char	padding;

	if (flags.zero_pad)
		ft_ncpytobuff(prefix, ft_strlen(prefix));
	if (size < (flags.precision + (int)ft_strlen(prefix)))
		size = flags.precision + ft_strlen(prefix);
	to_write = flags.min_length - size;
	if (to_write < 1)
		return (0);
	if (flags.zero_pad)
		padding = '0';
	else
		padding = ' ';
	while (to_write)
	{
		ft_writebuff(padding, 0);
		to_write--;
	}
	return (1);
}

static int		ft_precision(t_flags flags, int size)
{
	int to_write;

	if (size >= flags.precision)
		return (0);
	to_write = flags.precision - size;
	while (to_write)
	{
		ft_writebuff('0', 0);
		to_write--;
	}
	return (1);
}

static void		apply_prefix(t_flags *flags, char nbr[64], char prefix[3])
{
	if (flags->conversion == d)
	{
		if (flags->space)
			prefix[0] = ' ';
		else if (flags->put_sign)
			prefix[0] = '+';
	}
	else if ((flags->conversion == p)
			|| (flags->conversion == x) || (flags->conversion == X))
	{
		if (flags->alt_form)
			ft_strncpy(prefix, "0x", 2);
		if (flags->conversion == X)
		{
			str_upper(nbr);
			str_upper(prefix);
		}
	}
	else if ((flags->conversion == o) && (flags->alt_form))
	{
		if ((nbr[0] != '0') && (flags->precision <= (int)ft_strlen(nbr)))
			flags->precision = ft_strlen(nbr) + 1;
	}
}

static void		ft_vaarg_nbr(t_flags *flags, va_list ap, char nbr[64])
{
	ft_sanity(flags);
	if (flags->conversion == d)
		get_signed(*flags, nbr, ap);
	else
		get_unsigned(flags, nbr, ap);
}

int				ft_convert_nbr(t_flags *flags, va_list ap)
{
	char	nbr[64];
	char	prefix[3];
	int		size;

	ft_bzero(prefix, 3);
	ft_bzero(nbr, 64);
	ft_vaarg_nbr(flags, ap, nbr);
	if (nbr[0] == '-')
	{
		prefix[0] = nbr[0];
		ft_memmove(&nbr[0], &nbr[1], ft_strlen(nbr));
	}
	else
		apply_prefix(flags, nbr, prefix);
	size = ft_strlen(nbr) + ft_strlen(prefix);
	if (!flags->left_adj)
		ft_field_width(*flags, size, prefix);
	if (!flags->zero_pad)
		ft_ncpytobuff(prefix, ft_strlen(prefix));
	ft_precision(*flags, ft_strlen(nbr));
	ft_ncpytobuff(nbr, ft_strlen(nbr));
	if (flags->left_adj)
		ft_field_width(*flags, size, prefix);
	return (1);
}
