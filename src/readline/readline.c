/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:48:42 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/04 17:49:24 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_rdl	g_rdl;

char	*readline(char	*PROMPT)
{
	char	buf[11];
	int		ret;
	int		curs;

	rdlinit(&g_rdl);
	curs = 0;
	g_rdl.lpro = ft_printf("%s", PROMPT);
	g_rdl.prompt = PROMPT;
	g_rdl.col = getcolumn();
	setsig();
	while (42)
	{
		if ((ret = read(0, buf, 10)) < 0)
			break ;
		buf[ret] = 0;
		if (key_router(&g_rdl, buf))
			break ;
	}
	ft_putchar('\n');
	return (g_rdl.str);
}
