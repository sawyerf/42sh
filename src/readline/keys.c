/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:47:43 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/06 16:00:52 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_key	g_key[] = {
	{K_CTRA, &begin},
	{K_CTRC, &ctrlc},
	{K_CTRD, &ctrld},
	{K_BSPC, &del_cara},
	{K_RGHT, &move_curs},
	{K_LEFT, &move_curs},
	{K_SLFT, &prev_word},
	{K_SRGT, &next_word},
	{K_TAB,  &autocompl},
	{K_ENTR, &enter},
	{NULL, &special_key}
};

int		autocompl(t_rdl *rdl, char *buf)
{
	char	*c;

	c = rdl->str[rdl->curs];
	rdl->str[rdl->curs] = 0;
	rdl->str[rdl->curs] = c;
}

int		ctrlc(t_rdl *rdl, char *buf)
{
	(void)buf;
	rdl->str[0] = 0;
	return (1);
}

int		np_word(t_rdl *rdl, int i)
{
	int count;
	
	count = 0;
	if ((i < 0 && rdl->curs) || (i > 0 && rdl->str[rdl->curs]))
		count++;
	while (rdl->curs +  i * count >= 0 && rdl->str[rdl->curs +  i * count]
		&& (rdl->str[rdl->curs +  i * count] == ' '
			|| rdl->str[rdl->curs +  i * count] == '\n'))
		count++;
	while (rdl->curs +  i * count >= 0 && rdl->str[rdl->curs +  i * count]
		&& rdl->str[rdl->curs +  i * count] != ' '
			&& rdl->str[rdl->curs +  i * count] != '\n')
		count++;
	if (rdl->curs + i * count < 0)
		count = rdl->curs + 1;
	if (count)
		count--;
	return (count);
}

int		next_word(t_rdl *rdl, char *buf)
{
	int count;

	(void)buf;
	count = np_word(rdl, 1);
	right(count);
	rdl->curs += count;
	return (0);
}

int		prev_word(t_rdl *rdl, char *buf)
{
	int count;
	
	(void)buf;
	count = np_word(rdl, -1);
	left(count);
	rdl->curs -= count;
	return (0);
}
int		enter(t_rdl *rdl, char *buf)
{
	(void)rdl;
	(void)buf;
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

int		begin(t_rdl *rdl, char *buf)
{
	(void)buf;
	left(rdl->curs);
	rdl->curs = 0;
	return (0);
}

int		move_curs(t_rdl *rdl, char *buf)
{
	if (!ft_strcmp(K_RGHT, buf) && rdl->size > rdl->curs)
	{
		write(1, &rdl->str[rdl->curs], 1);
		rdl->curs++;
	}
	if (!ft_strcmp(K_LEFT, buf) && rdl->curs > 0)
	{
		rdl->curs--;
		write(1, K_LEFT, 3);
	}
	return (0);
}

int		del_cara(t_rdl *rdl, char *buf)
{
	(void)buf;
	rdldel(rdl, rdl->curs - 1);
	return (0);
}

int		special_key(t_rdl *rdl, char *buf)
{
	int count;

	count = 0;
	while (g_key[count].key)
	{
		if (!ft_strcmp(g_key[count].key, buf))
			return (g_key[count].f(rdl, buf));
		count++;
	}
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
		return (special_key(rdl, buf));
	else
		return (normal_key(rdl, buf));
}
