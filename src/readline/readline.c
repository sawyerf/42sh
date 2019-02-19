/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:48:42 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/19 17:02:37 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_rdl	g_rdl;

char	*readline(char	*PROMPT)
{
	char			buf[11];
	int				ret;
	int				stat;

	stat = 0;
	setsig();
	if (!terminit(&(g_rdl.save)) || rdlinit(&g_rdl, PROMPT) == MEMERR)
		return (NULL);
	while ((ret = read(0, buf, 10)) > 0)
	{
		buf[ret] = 0;
		if ((stat = key_router(&g_rdl, buf)))
			break ;
	}
	if (!termreset(&(g_rdl.save)) || stat == 2)
		ft_strdel(&g_rdl.str);
	return (g_rdl.str);
}
