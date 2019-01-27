/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 17:42:32 by ktlili            #+#    #+#             */
/*   Updated: 2018/07/22 13:47:02 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_strrev(char *str)
{
	int start;
	int end;

	start = 0;
	end = ft_strlen(str) - 1;
	if (end < 0)
		return ;
	while (start < end)
	{
		ft_swap_char((str + start), (str + end));
		start++;
		end--;
	}
}

int		ft_utoa_base(uintmax_t nbr, int base, char *str, int rev)
{
	intmax_t	towrite;
	int			i;

	i = 0;
	if (nbr == 0)
	{
		str[0] = '0';
		str[1] = 0;
		return (1);
	}
	while (nbr)
	{
		towrite = nbr % base;
		nbr = nbr / base;
		if (towrite > 9)
			str[i] = 'a' + (towrite - 10);
		else
			str[i] = '0' + towrite;
		i++;
	}
	towrite = i;
	str[i] = 0;
	if (rev)
		ft_strrev(str);
	return (i);
}

int		ft_inner_itoa(intmax_t nbr, int base, char *str)
{
	int			i;
	intmax_t	towrite;

	i = 0;
	while (nbr)
	{
		towrite = nbr % base;
		nbr = nbr / base;
		if (towrite > 9)
			str[i] = 'a' + (towrite - 10);
		else
		{
			if (towrite < 0)
				towrite = -towrite;
			str[i] = '0' + towrite;
		}
		i++;
	}
	return (i);
}

int		ft_itoa_base(intmax_t nbr, int base, char *str, int rev)
{
	int	i;
	int	negative;

	negative = 0;
	if (nbr == 0)
	{
		str[0] = '0';
		str[1] = 0;
		return (1);
	}
	if (nbr < 0)
	{
		nbr = -nbr;
		negative = 1;
	}
	i = ft_inner_itoa(nbr, base, str);
	if (negative)
	{
		str[i] = '-';
		i++;
	}
	str[i] = 0;
	if (rev)
		ft_strrev(str);
	return (i);
}
