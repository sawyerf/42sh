/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:49:43 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/01 17:10:15 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/*void	termreset()
{
	tcsetattr(0, TCSADRAIN, &(save));
}*/

int		terminit(struct termios *save)
{
	char			*tname;
	struct termios	term;

	if (!(tname = getenv("TERM")))
		exit(2);
	tgetent(NULL, tname);
	if (save)
		if (tcgetattr(0, save) == -1)
			return (0);
	if (tcgetattr(0, &term) == -1)
		return (0);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (0);
	return (1);
}

