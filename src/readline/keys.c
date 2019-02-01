/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:47:43 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/01 18:47:17 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_key	g_key[] = {
	{K_CTRA, &begin},
	{K_BSPC, &del_cara},
	{K_RGHT, &move_curs},
	{K_LEFT, &move_curs},
	{NULL, &special_key}
};

void	begin(t_rdl *rdl, char *buf)
{
	(void)buf;
	rdl->curs = 0;
}

void	move_curs(t_rdl *rdl, char *buf)
{
	if (!ft_strcmp(K_RGHT, buf) && rdl->size > rdl->curs)
		rdl->curs++;
	if (!ft_strcmp(K_LEFT, buf) && rdl->curs > 0)
		rdl->curs--;
}

void	del_cara(t_rdl *rdl, char *buf)
{
	(void)buf;
	rdldel(rdl, rdl->curs - 1);
}

void	special_key(t_rdl *rdl, char *buf)
{
	int count;

	count = 0;
	while (g_key[count].key)
	{
		if (!ft_strcmp(g_key[count].key, buf))
		{
			g_key[count].f(rdl, buf);
			return ;
		}
		count++;
	}
}

void	normal_key(t_rdl *rdl, char *buf)
{
	int count;

	count = 0;
	while (buf[count])
	{
		rdladd(rdl, buf[count]);
		count++;
	}
}

void	key_router(t_rdl *rdl, char *buf)
{
	if (is_special(buf))
		special_key(rdl, buf);
	else
		normal_key(rdl, buf);
}
