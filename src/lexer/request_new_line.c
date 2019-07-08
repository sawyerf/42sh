/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_new_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 19:58:10 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 19:58:14 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "ft_lexer.h"

int	request_new_line(t_lexer *lx_st)
{
	t_read_fn	read_fn;
	char		*new_line;
	char		*tmp;
	int			ret;

	read_fn = readline;
	if (g_sh.mode == NONINTERACTIVE)
		return (CTRL_D);
	if (g_sh.mode != INTERACTIVE)
		read_fn = sh_readfile;
	ret = read_fn("> ", &new_line);
	if (ret || !new_line)
		return (ret);
	tmp = ft_zprintf("%s%s", lx_st->line, new_line);
	ft_strdel(&new_line);
	if (!tmp)
		return (MEMERR);
	lx_st->cursor = tmp + ft_strlen(lx_st->line);
	ft_strdel(&lx_st->line);
	lx_st->line = tmp;
	return (0);
}
