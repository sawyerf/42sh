/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_other.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:28:09 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/01 18:28:33 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		end(t_rdl *rdl, char *buf)
{
	(void)buf;
	right(rdl, rdl->size - rdl->curs);
	rdl->curs += rdl->size - rdl->curs;
	return (0);
}

int		paste(t_rdl *rdl, char *buf)
{
	(void)buf;
	if (!rdl->paste)
		return (0);
	rdladdstr(rdl, rdl->paste);
	return (0);
}

int		del_cara(t_rdl *rdl, char *buf)
{
	(void)buf;
	rdldel(rdl, rdl->curs - 1);
	return (0);
}

int		ddel_cara(t_rdl *rdl, char *buf)
{
	(void)buf;
	rdldel(rdl, rdl->curs);
	return (0);
}
