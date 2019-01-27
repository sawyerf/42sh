/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstr_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 12:01:22 by ktlili            #+#    #+#             */
/*   Updated: 2018/07/17 12:36:52 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		ft_encode_wstr(wchar_t *wstr, int tocpy, char *buffer)
{
	int				bytecount;
	int				wchar_len;
	unsigned char	mbyte[4];

	bytecount = 0;
	while ((*wstr) && (bytecount < tocpy))
	{
		wchar_len = wint_to_mbyte(*wstr, mbyte);
		if (wchar_len < 1)
			return (-1);
		if ((mbyte[0] != 0) && ((bytecount + wchar_len) <= tocpy))
		{
			ft_strncpy(buffer, (char*)mbyte, wchar_len);
			buffer = buffer + wchar_len;
			bytecount = bytecount + wchar_len;
			wstr++;
		}
		else
			break ;
	}
	return (bytecount);
}

int		ft_insert_wstr(t_flags *flags, wchar_t *wstr)
{
	char	*temp_buffer;
	size_t	tocpy;
	int		bytecount;

	bytecount = 0;
	if (flags->precision > -1)
		tocpy = flags->precision;
	else
		tocpy = ft_wcslen(wstr) * sizeof(wchar_t);
	temp_buffer = ft_strnew(tocpy);
	if (temp_buffer == NULL)
		return (-1);
	bytecount = ft_encode_wstr(wstr, tocpy, temp_buffer);
	if (bytecount == -1)
	{
		free(temp_buffer);
		return (-1);
	}
	if (!flags->left_adj)
		ft_apply_minlen(flags, bytecount, select_padding(*flags));
	ft_ncpytobuff(temp_buffer, bytecount);
	if (flags->left_adj)
		ft_apply_minlen(flags, bytecount, ' ');
	free(temp_buffer);
	return (1);
}

int		ft_encode_wchar(wint_t toprint, unsigned char *mbyte)
{
	if (toprint < 0x7f)
		mbyte[0] = toprint;
	else if (toprint <= 0x7ff)
	{
		mbyte[0] = 0xc0 | (toprint >> 6);
		mbyte[1] = 0x80 | (toprint & 0x3f);
		return (2);
	}
	else if (toprint <= 0xffff)
	{
		mbyte[0] = 0xe0 | (toprint >> 12);
		mbyte[1] = 0x80 | ((toprint >> 6) & 0x3f);
		mbyte[2] = 0x80 | (toprint & 0x3f);
		return (3);
	}
	else if (toprint <= 0x10ffff)
	{
		mbyte[0] = 0xf0 | (toprint >> 18);
		mbyte[1] = 0x80 | ((toprint >> 12) & 0x3f);
		mbyte[2] = 0x80 | ((toprint >> 6) & 0x3f);
		mbyte[3] = 0x80 | (toprint & 0x3f);
		return (4);
	}
	return (1);
}

int		wint_to_mbyte(wint_t toprint, unsigned char *mbyte)
{
	if (MB_CUR_MAX == 1)
	{
		if (toprint > 0xFF)
			return (-1);
		mbyte[0] = (char)toprint;
		return (1);
	}
	if (((toprint >= 0xd800) && (toprint <= 0xdfff))
			|| (toprint > 0x10ffff))
		return (-1);
	return (ft_encode_wchar(toprint, mbyte));
}

size_t	ft_wcslen(wchar_t *wstr)
{
	size_t len;

	len = 0;
	while (*wstr)
	{
		len++;
		wstr++;
	}
	return (len);
}
