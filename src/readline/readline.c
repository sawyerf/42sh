/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:48:42 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/06 18:53:24 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_rdl	g_rdl;

char	*readline(char	*PROMPT)
{
	char	buf[11];
	int		ret;
	int		stat;

	setsig();
	rdlinit(&g_rdl, PROMPT);
	if (!terminit(&(g_rdl.save)))
		return (NULL);
	stat = 0;
	while (42)
	{
		if ((ret = read(0, buf, 10)) < 0)
			break ;
		buf[ret] = 0;
		if ((stat = key_router(&g_rdl, buf)))
			break ;
	}
	ft_putchar('\n');
	termreset(&(g_rdl.save));
	if (stat == 2)
		exit(1);
	return (g_rdl.str);
}
