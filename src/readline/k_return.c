/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_return.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 21:18:26 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/18 17:31:58 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		ctrlc(t_rdl *rdl, char *buf)
{
	(void)buf;
	right(rdl, rdl->size - rdl->curs);
	rdl->str[0] = 0;
	rdl->size = 0;
	rdl->curs = 0;
	return (1);
}

int		enter(t_rdl *rdl, char *buf)
{
	(void)buf;
	right(rdl, rdl->size - rdl->curs);
	rdl->curs = rdl->size;
	hstadd(rdl->str);
	hstreset();
	rdladd(rdl, '\n');
	return (1);
}

int		ctrld(t_rdl *rdl, char *buf)
{
	(void)buf;
	if (!rdl->str[0])
	{
		write(1, "\n", 1);
		return (2);
	}
	return (0);
}
