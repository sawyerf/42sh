/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:37:16 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/04 14:52:01 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

extern t_rdl g_rdl;

void	resize(int sig)
{
	(void)sig;
	g_rdl.col = getcolumn();
}

void	setsig(void)
{
	signal(SIGWINCH, &resize);
}
