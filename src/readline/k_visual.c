/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_select.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 12:42:13 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/01 18:06:44 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_key	g_vskey[] =\
{
	{K_RGHT, vm_move},
	{K_LEFT, vm_move},
	{K_ESC, finish},
	{K_CTRC, finish},
	{K_CTRV, finish},
	{K_CTRY, vm_copy},
	{K_CTRX, vm_cut},
	{K_CTRD, vm_del},
	{NULL, vm_move}
};

int		finish(t_rdl *rdl, char *buf)
{
	(void)rdl;
	(void)buf;
	return (1);
}

int		vm_cut(t_rdl *rdl, char *buf)
{
	if (vm_copy(rdl, buf) == MEMERR)
		return (MEMERR);
	return (vm_del(rdl, buf));
}

int		vm_del(t_rdl *rdl, char *buf)
{
	int len;

	(void)buf;
	len = rdl->curs - rdl->vcurs;
	if (len < 0)
	{
		len *= -1;
		right(rdl, len);
		rdl->curs += len;
	}
	while (len)
	{
		rdldel(rdl, rdl->curs - 1);
		len--;
	}
	return (1);
}

int		vm_copy(t_rdl *rdl, char *buf)
{
	int	start;
	int len;

	(void)buf;
	len = rdl->curs - rdl->vcurs;
	if (rdl->vcurs < rdl->curs)
		start = rdl->vcurs;
	else
		start = rdl->curs;
	if (len < 0)
		len = -len;
	if (!(rdl->paste = ft_strndup(&rdl->str[start], len)))
		return (MEMERR);
	return (1);
}

int		visualmode(t_rdl *rdl, char *key)
{
	char	buf[11];
	int		ret;

	(void)key;
	rdl->vcurs = rdl->curs;
	while (42)
	{
		if (!(ret = read(0, &buf, 10)))
			return (-1);
		buf[ret] = 0;
		if (special_key(rdl, buf, g_vskey))
			break ;
		buf[0] = 0;
	}
	reprint(rdl, rdl->curs);
	if (ret == MEMERR)
		return (MEMERR + 1);
	return (0);
}
