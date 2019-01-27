/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 13:14:28 by ktlili            #+#    #+#             */
/*   Updated: 2018/07/17 12:49:34 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_handle_arg(const char **format, t_flags *flags, va_list ap)
{
	char	percent;
	int		ret;

	ret = 1;
	percent = '%';
	ft_bzero(flags, sizeof(t_flags));
	if (ft_parser(format, flags) != 1)
		return (0);
	if (flags->conversion == 14)
	{
		flags->conversion = c;
		ft_insert_str(flags, &percent);
		return (1);
	}
	if ((flags->conversion < p) || (flags->conversion > X))
		ret = ft_convert_str(flags, ap);
	else
		ret = ft_convert_nbr(flags, ap);
	return (ret);
}

static int	ft_main_loop(const char *format, va_list ap)
{
	t_flags flags;
	int		i;

	i = 0;
	while (format[i] != 0)
	{
		if (format[i] == '%')
		{
			format = format + i + 1;
			if (ft_handle_arg(&format, &flags, ap) == -1)
				return (-1);
			i = 0;
			if (format[i] == 0)
				break ;
		}
		else
		{
			ft_writebuff(format[i], 0);
			i++;
		}
	}
	return (0);
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	if (ft_main_loop(format, ap) == -1)
	{
		ft_writebuff(0, 1);
		return (-1);
	}
	va_end(ap);
	ret = ft_writebuff(0, 1);
	return (ret);
}
