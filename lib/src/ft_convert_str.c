/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 22:24:31 by ktlili            #+#    #+#             */
/*   Updated: 2018/09/12 00:05:56 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void			ft_apply_minlen(t_flags *flags, int tocpy, char padding)
{
	while ((flags->min_length - tocpy) > 0)
	{
		ft_writebuff(padding, 0);
		flags->min_length--;
	}
}

void			ft_insert_str(t_flags *flags, char *str)
{
	char	padding;
	int		tocpy;

	if (flags->conversion == c)
		tocpy = 1;
	else if ((ft_strlen(str) == 0) || (flags->precision == -1)
			|| (flags->precision > (int)ft_strlen(str)))
		tocpy = ft_strlen(str);
	else
		tocpy = flags->precision;
	padding = ' ';
	if ((!flags->left_adj) && (flags->zero_pad))
		padding = '0';
	if (flags->left_adj)
	{
		ft_ncpytobuff(str, tocpy);
		ft_apply_minlen(flags, tocpy, padding);
	}
	else
	{
		ft_apply_minlen(flags, tocpy, padding);
		ft_ncpytobuff(str, tocpy);
	}
}

static	int		ft_handle_c(t_flags *flags, va_list ap)
{
	char			c;
	wchar_t			wchar;
	unsigned char	mbyte[4];
	int				wchar_len;

	if (flags->length_mod == none)
	{
		c = (unsigned char)va_arg(ap, int);
		ft_insert_str(flags, (char*)&c);
		return (1);
	}
	else if (flags->length_mod == l)
	{
		wchar = (wchar_t)va_arg(ap, wint_t);
		wchar_len = wint_to_mbyte(wchar, mbyte);
		if ((wchar_len < 1) || (wchar < 0))
			return (-1);
		if (!flags->left_adj)
			ft_apply_minlen(flags, wchar_len, select_padding(*flags));
		ft_ncpytobuff((char*)mbyte, wchar_len);
		if (flags->left_adj)
			ft_apply_minlen(flags, wchar_len, ' ');
	}
	return (1);
}

static	int		ft_handle_s(t_flags *flags, va_list ap)
{
	char	*str;
	wchar_t	*wstr;
	char	null_str[10];

	ft_strncpy(null_str, "(null)", 6);
	null_str[6] = 0;
	if (flags->length_mod == none)
	{
		str = va_arg(ap, char*);
		if (str == NULL)
			str = null_str;
		ft_insert_str(flags, str);
	}
	else if (flags->length_mod == l)
	{
		wstr = va_arg(ap, wchar_t*);
		if (wstr == NULL)
		{
			ft_insert_wstr(flags, L"(null)");
			return (1);
		}
		if (ft_insert_wstr(flags, wstr) == -1)
			return (-1);
	}
	return (1);
}

int				ft_convert_str(t_flags *flags, va_list ap)
{
	int ret;

	ret = 0;
	ft_str_sanity(flags);
	if (flags->conversion == c)
		ret = ft_handle_c(flags, ap);
	else if (flags->conversion == s)
		ret = ft_handle_s(flags, ap);
	return (ret);
}
