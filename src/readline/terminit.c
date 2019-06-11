/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:49:43 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/03 16:43:16 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <sys/ioctl.h>

int		termreset(struct termios *save)
{
	if (tcsetattr(0, TCSADRAIN, save) == -1)
	{
		ft_dprintf(2, "21sh: tcsetattr fail to set the old param\n");
		return (0);
	}
	return (1);
}

void	printmagicdollar(void)
{
	int	n;
	int	i[2];

	if (ioctl(0, FIONREAD, &n) < 0)
		return ;
	if (!n)
	{
		get_cursor_position(&i[0], &i[1]);
		if (i[0] > 0)
			ft_printf("\033[1;7m%%\033[1;0m\n");
	}
}

int		terminit(struct termios *save)
{
	char			*tname;
	char			buf[2048];
	struct termios	term;

	if (!(tname = getenv("TERM")))
	{
		ft_dprintf(2, "21sh: TERM not set\n");
		return (0);
	}
	tgetent(buf, tname);
	if (save)
		if (tcgetattr(0, save) == -1)
			return (0);
	if (tcgetattr(0, &term) == -1)
		return (0);
	term.c_lflag &= ~(ICANON | ISIG | IEXTEN);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (0);
	printmagicdollar();
	return (1);
}
