/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:47:43 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/08 17:51:23 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "sh_core.h"

t_key	g_key[] =\
{
	{K_HOME, &begin},
	{K_END, &end},
	{K_CTRA, &begin},
	{K_CTRC, &ctrlc},
	{K_CTRD, &ctrld},
	{K_CTRP, &paste},
	{K_CTRV, &visualmode},
	{K_CTRR, &ctrlr},
	{K_BSPC, &del_cara},
	{K_DEL, &ddel_cara},
	{K_RGHT, &move_curs},
	{K_LEFT, &move_curs},
	{K_UP, &history},
	{K_DOWN, &history},
	{K_SLFT, &prev_word},
	{K_SRGT, &next_word},
	{K_SUP, &move_curs},
	{K_SDOW, &move_curs},
	{K_TAB, &autocompl},
	{K_ENTR, &enter},
	{NULL, &enter}
};

int		special_key(t_rdl *rdl, char *buf, t_key *key)
{
	int count;

	count = 0;
	while (key[count].key)
	{
		if (!ft_strcmp(key[count].key, buf))
			return (key[count].f(rdl, buf));
		count++;
	}
	tgpstr("vb");
	return (0);
}

int		normal_key(t_rdl *rdl, char *buf)
{
	int count;

	count = 0;
	while (buf[count])
	{
		rdladd(rdl, buf[count]);
		count++;
	}
	return (0);
}

int		key_router(t_rdl *rdl, char *buf)
{
	if (is_special(buf))
		return (special_key(rdl, buf, g_key));
	else
		return (normal_key(rdl, buf));
}
