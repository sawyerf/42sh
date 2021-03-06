/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:37:16 by apeyret           #+#    #+#             */
/*   Updated: 2019/07/09 11:11:16 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

extern t_rdl g_rdl;

void	resize(int sig)
{
	(void)sig;
	g_rdl.col = getcolumn();
	reprint(&g_rdl, g_rdl.curs);
}

void	nothing(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	setsig(void)
{
	signal(SIGWINCH, &resize);
	signal(SIGINT, &nothing);
}

void	unsetsig(void)
{
	signal(SIGWINCH, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
