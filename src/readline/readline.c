/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:48:42 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/01 18:20:05 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char	*readline(char	*PROMPT)
{
	char	buf[11];
	int		ret;
	int		curs;
	t_rdl	rdl;

	rdlinit(&rdl);
	ft_printf("%s\n", PROMPT);
	curs = 0;
	while (42)
	{
		if ((ret = read(0, buf, 10)) < 0)
			break ;
		buf[ret] = 0;
		key_router(&rdl, buf);
		ft_printf("%d%s%s\n", rdl.curs, PROMPT, rdl.str);
	}
	return (rdl.str);
}
