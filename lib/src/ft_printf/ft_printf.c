/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 14:08:18 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/26 15:04:20 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_cpy_spec(t_printf *lst, char *tmp)
{
	lst->opt.tmp = tmp;
	if (lst->type == 'c')
	{
		pf_options("*", lst->opt);
		pf_replace(tmp, '*', lst->var[0], lst->len);
	}
	else
		pf_options(lst->var, lst->opt);
	if (lst->type == 'x' || lst->type == 'p')
		ft_strlower(lst->opt.tmp);
}

char	*ret(t_printf *lst, int len)
{
	char	*s;
	char	*tmp;

	if (!(s = ft_strnew(len)))
		return (NULL);
	tmp = s;
	while (lst)
	{
		if (!lst->var)
			return (s);
		if (!lst->needconv)
			ft_strcpy(tmp, lst->var);
		else
			pf_cpy_spec(lst, tmp);
		tmp += lst->len;
		lst = lst->next;
	}
	return (s);
}

int		ft_printf(const char *format, ...)
{
	t_printf	*lst;
	va_list		ap;
	int			len;
	char		*s;

	lst = pf_parser(format);
	if (!lst)
		return (0);
	va_start(ap, format);
	pf_router(lst, ap);
	len = lenall(lst);
	s = ret(lst, len);
	write(1, s, len);
	free(s);
	pf_prdel(lst);
	return (len);
}

int		ft_dprintf(int fd, const char *format, ...)
{
	t_printf	*lst;
	va_list		ap;
	int			len;
	char		*s;

	lst = pf_parser(format);
	if (!lst)
		return (0);
	va_start(ap, format);
	pf_router(lst, ap);
	len = lenall(lst);
	s = ret(lst, len);
	write(fd, s, len);
	free(s);
	pf_prdel(lst);
	return (len);
}

char	*ft_zprintf(const char *format, ...)
{
	t_printf	*lst;
	char		*s;
	va_list		ap;
	int			len;

	lst = pf_parser(format);
	if (!lst)
		return (0);
	va_start(ap, format);
	pf_router(lst, ap);
	len = lenall(lst);
	s = ret(lst, len);
	pf_prdel(lst);
	return (s);
}
