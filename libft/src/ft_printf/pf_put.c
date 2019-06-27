/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 14:09:10 by apeyret           #+#    #+#             */
/*   Updated: 2019/01/16 14:10:05 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putstrr(char *str, char c)
{
	int count;

	count = 0;
	while (str[count])
	{
		if (str[count] == 42)
			ft_putchar(c);
		else
			ft_putchar(str[count]);
		count++;
	}
}

char	*pf_putchar(t_printf *lst, const char c)
{
	t_opt	opt;

	if (!(lst->var = ft_strnew(1)))
		return (NULL);
	lst->var[0] = c;
	opt = pf_optnew();
	opt.size = 1;
	if (lst->pre[0] > 1 && ft_cisin(lst->settings, '-'))
		opt.nb_spe = lst->pre[0] - 1;
	else if (lst->pre[0] > 1 && ft_cisin(lst->settings, '0'))
		opt.nb_0 = lst->pre[0] - 1;
	else if (lst->pre[0] > 1)
		opt.nb_sp = lst->pre[0] - 1;
	lst->len = opt.size + opt.nb_spe + opt.nb_0 + opt.nb_sp;
	lst->opt = opt;
	return (lst->var);
}

char	*pf_putstr(t_printf *lst, const char *s)
{
	t_opt opt;

	opt = pf_optnew();
	if (!s)
		if (!(lst->var = ft_strdup("(null)")))
			return (NULL);
	if (s)
		if (!(lst->var = ft_strdup(s)))
			return (NULL);
	opt.size = ft_strlen(lst->var);
	if (lst->pre[1] < opt.size && lst->pre[2])
		opt.size = lst->pre[1];
	if (lst->pre[0] > opt.size && ft_cisin(lst->settings, '-'))
		opt.nb_spe = lst->pre[0] - opt.size;
	else if (lst->pre[0] > opt.size && ft_cisin(lst->settings, '0'))
		opt.nb_0 = lst->pre[0] - opt.size;
	else if (lst->pre[0] > opt.size)
		opt.nb_sp = lst->pre[0] - opt.size;
	lst->len = opt.size + opt.nb_spe + opt.nb_0 + opt.nb_sp;
	lst->opt = opt;
	return (lst->var);
}

char	*pf_putaddr(t_printf *lst, void *addr)
{
	t_opt	opt;

	opt = pf_optnew();
	opt.nb_zero = 2;
	if (!(lst->var = utoa_base(lst, (unsigned long)(addr), 16)))
		return (NULL);
	opt.size = ft_strlen(lst->var);
	if (!lst->pre[1] && lst->pre[2] && lst->var[0] == '0')
		opt.size = 0;
	else if (lst->pre[1] > opt.size)
		opt.nb_0 = lst->pre[1] - opt.size;
	if (lst->pre[0] > opt.size + 2 && ft_cisin(lst->settings, '-'))
		opt.nb_spe = lst->pre[0] - opt.size - 2;
	else if (lst->pre[0] > opt.size + 2 && ft_cisin(lst->settings, '0'))
		opt.nb_0 = lst->pre[0] - opt.size - 2;
	else if (lst->pre[0] > opt.size + opt.nb_0 + 2)
		opt.nb_sp = lst->pre[0] - opt.size - opt.nb_0 - 2;
	lst->len = opt.size + opt.nb_zero + opt.nb_sp + opt.nb_spe + opt.nb_0;
	lst->opt = opt;
	return (lst->var);
}
