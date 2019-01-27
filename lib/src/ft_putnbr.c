/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 22:45:13 by ktlili            #+#    #+#             */
/*   Updated: 2018/07/22 13:52:17 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>

static int	ft_intlen(int n)
{
	int len;

	len = 0;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	if (len < 0)
		len = -len;
	return (len);
}

static int	ft_power(int x, int y)
{
	int num;

	num = x;
	if (y == 0)
		return (1);
	while (y > 1)
	{
		x = x * num;
		y--;
	}
	return (x);
}

void		ft_putnbr(int n)
{
	int				len;
	int				num;
	long long int	lint;

	lint = n;
	if (lint < 0)
	{
		ft_putchar('-');
		lint = -lint;
	}
	if (lint == 0)
	{
		ft_putchar('0');
		return ;
	}
	len = ft_intlen(lint);
	while (len > 0)
	{
		num = lint / (ft_power(10, len - 1));
		ft_putchar(num + '0');
		lint = lint - (num * ft_power(10, len - 1));
		len--;
	}
}
