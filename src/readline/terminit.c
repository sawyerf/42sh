/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:49:43 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/27 16:20:50 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "sh_core.h"
#include <sys/ioctl.h>

int		termreset(struct termios *save)
{
	if (tcsetattr(0, TCSADRAIN, save) == -1)
	{
		ft_dprintf(2, "42sh: tcsetattr fail to set the old param\n");
		return (0);
	}
	return (1);
}

void	printmagicdollar(void)
{
	int	col;

	col = getcolumn();
	if (col - 1 < 0)
		return ;
	ft_printf("\033[1;7m%%\033[1;0m%*c", col - 1, ' ');
	tgpstr("cr");
	tgpstr("cd");
}

int		terminit(struct termios *save)
{
	char			buf[2048];
	char			tname[1024];
	struct termios	term;

	tname[0] = 0;
	if (!get_env_value("TERM"))
		cexport("TERM=xterm-256color");
	ft_strcpy(tname, get_env_value("TERM"));
	tgetent(buf, tname);
	if (save)
		if (tcgetattr(0, save) == -1)
			return (0);
	if (tcgetattr(0, &term) == -1)
		return (0);
	term.c_lflag &= ~(ICANON | ISIG | IEXTEN);
	term.c_lflag &= ~(ECHO | TOSTOP);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (0);
	printmagicdollar();
	return (1);
}
