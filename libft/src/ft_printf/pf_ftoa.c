/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 14:08:47 by apeyret           #+#    #+#             */
/*   Updated: 2019/01/16 14:09:58 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long			ft_pow(long long n, int pow)
{
	long long	total;

	total = n;
	if (!pow)
		return (1);
	if (pow == 1)
		return (n);
	while (--pow)
		total *= n;
	return (total);
}

void				copy(char *ptr, int *i, long long ipart, long long n)
{
	while (n)
	{
		ptr[(*i)++] = (ipart / n) + '0';
		ipart %= n;
		n /= 10;
	}
	ptr[*i] = '\0';
}

int					len_cal(long nb, int base)
{
	int		i;

	i = 1;
	while (nb /= base)
		++i;
	return (i);
}

char				*pf_ftoa_exep(t_printf *lst, double n)
{
	long long		ipart;
	int				len;
	int				i;
	int				p;

	p = (lst->pre[1]) ? lst->pre[1] : 0;
	ipart = (long long)n;
	ipart = (n < 0) ? -ipart : ipart;
	len = len_cal(ipart, 10);
	ipart = ((ipart % ft_pow(10, len)) > 5) ? ipart + 1 : ipart;
	if (!(lst->var = (n < 0) ? ft_strnew(len + p + 1) : ft_strnew(len + p + 2)))
		return (NULL);
	i = 0;
	if (n < 0)
		lst->var[i++] = '-';
	copy(lst->var, &i, ipart, ft_pow(10, len - 1));
	return (lst->var);
}

char				*pf_ftoa(t_printf *lst, double n)
{
	long long		ipart;
	long double		dpart;
	int				len;
	int				i;
	int				p;

	p = (lst->pre[1]) ? lst->pre[1] : 6;
	ipart = (long long)n;
	dpart = n - (long double)ipart;
	ipart = (n < 0) ? -ipart : ipart;
	dpart = (n < 0) ? -dpart : dpart;
	dpart *= ft_pow(10, p);
	len = len_cal(ipart, 10);
	if (!(lst->var = (n < 0) ? ft_strnew(len + p + 1) : ft_strnew(len + p + 2)))
		return (NULL);
	i = 0;
	if (n < 0)
		lst->var[i++] = '-';
	copy(lst->var, &i, ipart, ft_pow(10, len - 1));
	lst->var[i++] = '.';
	dpart = ((long long)((dpart - (long long)dpart) * 10) > 5) ?
		dpart + 1 : dpart;
	copy(lst->var, &i, dpart, ft_pow(10, p - 1));
	return (lst->var);
}
