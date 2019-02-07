/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_router.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 14:09:16 by apeyret           #+#    #+#             */
/*   Updated: 2019/01/22 21:20:26 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_router_d(t_printf *lst, va_list ap)
{
	if (lst->size[1] == 'l')
		stoa_base(lst, va_arg(ap, long long), pf_base(lst->type));
	else if (lst->size[0] == 'l' || lst->type == 'D')
		stoa_base(lst, va_arg(ap, long), pf_base(lst->type));
	else if (lst->size[1] == 'h')
		stoa_base(lst, (char)va_arg(ap, int), pf_base(lst->type));
	else if (lst->size[0] == 'h')
		stoa_base(lst, (short)va_arg(ap, int), pf_base(lst->type));
	else if (lst->size[0] == 'z')
		stoa_base(lst, va_arg(ap, ssize_t), pf_base(lst->type));
	else if (lst->size[0] == 'j')
		stoa_base(lst, va_arg(ap, intmax_t), pf_base(lst->type));
	else if (lst->size[0] == '\0')
		stoa_base(lst, va_arg(ap, int), pf_base(lst->type));
	if (lst->var)
		lst->opt = pf_len(lst, pf_optnew());
}

void	pf_router_u(t_printf *lst, va_list ap)
{
	if (lst->size[1] == 'l' || lst->type == 'U')
		utoa_base(lst, va_arg(ap, unsigned long long), pf_base(lst->type));
	else if (lst->size[0] == 'l' || lst->type == 'O')
		utoa_base(lst, va_arg(ap, unsigned long), pf_base(lst->type));
	else if (lst->size[1] == 'h')
		utoa_base(lst, (unsigned char)va_arg(ap, unsigned int),
				pf_base(lst->type));
	else if (lst->size[0] == 'h')
		utoa_base(lst, (unsigned short)va_arg(ap, unsigned int),
				pf_base(lst->type));
	else if (lst->size[0] == 'z')
		utoa_base(lst, va_arg(ap, size_t), pf_base(lst->type));
	else if (lst->size[0] == 'j')
		utoa_base(lst, va_arg(ap, uintmax_t), pf_base(lst->type));
	else if (lst->size[0] == '\0')
		utoa_base(lst, va_arg(ap, unsigned int), pf_base(lst->type));
	if (lst->var)
		lst->opt = pf_lenu(lst, pf_optnew());
}

void	pf_router_f(t_printf *lst, va_list ap)
{
	if (!lst->pre[1] && lst->pre[2])
		pf_ftoa_exep(lst, va_arg(ap, double));
	else
		pf_ftoa(lst, va_arg(ap, double));
	if (lst->var)
		lst->opt = pf_len_f(lst, pf_optnew());
}

void	pf_wildcard(t_printf *lst, va_list ap)
{
	if (lst->pre[0] == -1)
		lst->pre[0] = va_arg(ap, int);
	if (lst->pre[1] == -1)
		lst->pre[1] = va_arg(ap, int);
}

void	pf_router(t_printf *lst, va_list ap)
{
	t_printf	*tmp;

	tmp = lst;
	while (tmp)
	{
		pf_wildcard(tmp, ap);
		if (!tmp->needconv && tmp->var)
			tmp->len = ft_strlen(tmp->var);
		else if (ft_cisin("fF", tmp->type))
			pf_router_f(tmp, ap);
		else if (tmp->type == 's')
			pf_putstr(tmp, va_arg(ap, char*));
		else if (tmp->type == 'c')
			pf_putchar(tmp, va_arg(ap, int));
		else if (ft_cisin("diD", tmp->type))
			pf_router_d(tmp, ap);
		else if (ft_cisin("uoxXbUu", tmp->type))
			pf_router_u(tmp, ap);
		else if (tmp->type == 'p')
			pf_putaddr(tmp, va_arg(ap, void*));
		else
			pf_putchar(tmp, tmp->type);
		tmp = tmp->next;
	}
}
