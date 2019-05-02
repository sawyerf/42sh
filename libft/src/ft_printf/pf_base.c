/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_base.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 14:09:48 by apeyret           #+#    #+#             */
/*   Updated: 2019/01/16 14:09:53 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char				*stoa_base(t_printf *lst, long long n, int b)
{
	unsigned long long	nb;
	int					i;

	i = 0;
	nb = (n < 0) ? (-n) : n;
	i = (b == 10 && n < 0) ? 2 : 1;
	while (nb /= b)
		++i;
	nb = (n < 0) ? (-n) : n;
	if (!(lst->var = ft_strnew(i)))
		return (NULL);
	while (i--)
	{
		lst->var[i] = (nb % b < 10) ? (nb % b + '0') : (nb % b + 'A' - 10);
		nb /= b;
	}
	if (i && n < 0 && b == 10)
		lst->var[0] = '-';
	return (lst->var);
}

char				*utoa_base(t_printf *lst, unsigned long long n, int b)
{
	unsigned long long	nb;
	int					i;

	i = 1;
	nb = n;
	while (nb /= b)
		++i;
	if (!(lst->var = ft_strnew(i)))
		return (NULL);
	while (i--)
	{
		lst->var[i] = (n % b < 10) ? (n % b + '0') : (n % b + 'A' - 10);
		n /= b;
	}
	return (lst->var);
}
