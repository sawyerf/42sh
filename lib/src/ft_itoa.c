/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 17:05:36 by ktlili            #+#    #+#             */
/*   Updated: 2018/07/22 13:52:17 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int		ft_intlen(int n)
{
	int len;

	len = 0;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void		ft_sign(int n, int *sign, long long int *x)
{
	if ((n < 0) | (n == 0))
	{
		*sign = 1;
		*x = -n;
		if (*x < 0)
			*x = -(*x);
	}
	else
	{
		*x = n;
		*sign = 0;
	}
}

char			*ft_itoa(int n)
{
	int				len;
	long long int	x;
	int				sign;
	char			*ret;

	len = ft_intlen(n);
	ft_sign(n, &sign, &x);
	ret = (char *)malloc((len + sign + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ret[len + sign] = '\0';
	ret[0] = '0';
	if (x == 0)
		return (&ret[0]);
	if (sign != 0)
		ret[0] = '-';
	else
		len--;
	while (x != 0)
	{
		ret[len] = (x % 10) + '0';
		len--;
		x = x / 10;
	}
	return (&ret[0]);
}
