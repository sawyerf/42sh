/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_history.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 13:41:29 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/19 17:50:58 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		history(t_rdl *rdl, char *buf)
{
	char	*new;

	new = NULL;
	if (!ft_strcmp(K_UP, buf))
		new = hstnext(rdl->str);
	else if (!ft_strcmp(K_DOWN, buf))
		new = hstprev();
	if (!new)
		return (0);
	rdlreplace(rdl, new);
	return (0);
}
