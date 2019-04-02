/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:49:43 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/02 17:50:02 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		tputchar(int c)
{
	return (write(1, &c, 1));
}

int		getcolumn(void)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col);
}

void	tgpstr(char *s)
{
	char	*str;

	if (!(str = tgetstr(s, NULL)))
		return ;
	tputs(str, 0, tputchar);
}

void	get_cursor_position(int *col, int *rows)
{
	int		i;
	char	buf[17];

	write(1, "\033[6n", 4);
	if ((i = read(0, buf, 16)) <= 0)
		return ;
	buf[i] = 0;
	i = 0;
	while (buf[i])
	{
		if (buf[i] == '[')
			*rows = ft_atoi(&buf[i + 1]) - 1;
		if (buf[i] == ';')
			*col = ft_atoi(&buf[i + 1]) - 1;
		i++;
	}
}
