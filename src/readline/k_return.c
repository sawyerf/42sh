/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_return.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 21:18:26 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/12 21:18:30 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		ctrlc(t_rdl *rdl, char *buf)
{
	(void)buf;
	rdl->str[0] = 0;
	return (1);
}

int		enter(t_rdl *rdl, char *buf)
{
	(void)buf;
	right(rdl, rdl->size - rdl->curs);
	rdladd(rdl, '\n');
	return (1);
}

int		ctrld(t_rdl *rdl, char *buf)
{
	(void)buf;
	if (!rdl->str[0])
	{
		ft_strdel(&rdl->str);
		write(1, "\n", 1);
		termreset(&rdl->save);
		exit(1);
	}
	return (0);
}
