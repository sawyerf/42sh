/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:58:04 by ktlili            #+#    #+#             */
/*   Updated: 2018/07/17 11:12:47 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	get_level0(const char **input, t_flags *flags)
{
	if (**input == '#')
		flags->alt_form = 1;
	else if (**input == '0')
		flags->zero_pad = 1;
	else if (**input == '-')
		flags->left_adj = 1;
	else if (**input == '+')
		flags->put_sign = 1;
	else if (**input == ' ')
		flags->space = 1;
	else
		return (0);
	*input = *input + 1;
	return (1);
}

int	get_min_len(const char **input, t_flags *flags)
{
	int min_len;

	if ((**input < 48) || (**input > 57))
		return (0);
	min_len = ft_atoi(*input);
	flags->min_length = min_len;
	while (ft_isdigit(**input))
		*input = *input + 1;
	return (1);
}

int	get_precision(const char **input, t_flags *flags)
{
	int prec;

	if (**input != '.')
	{
		return (0);
	}
	*input = *input + 1;
	if (!ft_isdigit(**input))
	{
		flags->precision = 0;
		return (1);
	}
	prec = ft_atoi(*input);
	flags->precision = prec;
	while (ft_isdigit(**input))
		*input = *input + 1;
	return (1);
}

int	get_lmod(const char **input, t_flags *flags)
{
	static char		lmod[7][3] = {"hh", "h", "ll", "l", "j", "z"};
	int				cmp;
	unsigned int	i;

	cmp = 1;
	i = 0;
	while (i < 6)
	{
		cmp = ft_strncmp(lmod[i], *input, ft_strlen(lmod[i]));
		if (cmp == 0)
		{
			if ((i + 1) > flags->length_mod)
				flags->length_mod = i + 1;
			*input = *input + ft_strlen(lmod[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_conversion(const char **input, t_flags *flags)
{
	static char	*conversion = "sSpdDioOuUxXcC%";
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(conversion);
	while (i < len)
	{
		if (**input == conversion[i])
		{
			flags->conversion = i;
			*input = *input + 1;
			return (1);
		}
		i++;
	}
	return (-1);
}
