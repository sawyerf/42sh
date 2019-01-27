/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 16:42:39 by ktlili            #+#    #+#             */
/*   Updated: 2018/07/17 11:04:00 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_sanity_unsigned(t_flags *flags)
{
	if ((flags->conversion > 5) && (flags->conversion < 12))
	{
		if (flags->conversion == O)
		{
			flags->length_mod = l;
			flags->conversion = o;
		}
		if (flags->conversion == U)
		{
			flags->length_mod = l;
			flags->conversion = u;
		}
		flags->space = 0;
		flags->put_sign = 0;
	}
}

void	ft_sanity(t_flags *flags)
{
	if ((flags->conversion == D) || (flags->conversion == i)
			|| (flags->conversion == d))
	{
		if (flags->conversion == D)
			flags->length_mod = l;
		flags->conversion = d;
		flags->alt_form = 0;
		if ((flags->put_sign) && (flags->space))
			flags->space = 0;
	}
	ft_sanity_unsigned(flags);
	if (((flags->zero_pad) && (flags->left_adj)) || (flags->precision >= 0))
		flags->zero_pad = 0;
	if (flags->conversion == p)
	{
		flags->length_mod = l;
		flags->alt_form = 1;
	}
}

void	ft_str_sanity(t_flags *flags)
{
	if ((flags->conversion == S) || (flags->conversion == C))
	{
		flags->length_mod = l;
		if (flags->conversion == S)
			flags->conversion = s;
		else
			flags->conversion = c;
	}
}
