/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 18:14:11 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/01 14:08:21 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"


void			init_iterator(int *read, int *write)
{
	*read = 0;
	*write = 0;
}

int				expand_tokens(char **arg)
{
(void)arg;
/*	int		read;
	int		write;
	char	*tmp;

	init_iterator(&read, &write);
	while (arg[read] != NULL)
	{
		if ((arg[read][0] == '~') && (tilde_valid(&arg[read][1])))
		{
			if (handle_tilde(arg, &tmp, write, read) != 0)
				return (MEMERR);
		}
		tmp = expand_dollar(arg[read]);
		if (tmp == NULL)
			return (MEMERR);
		free(arg[write]);
		arg[write] = tmp;
		if (arg[write][0] != 0)
			write++;
		read++;
	}
	if (arg[write] != NULL)
		free_tab_bytes(&arg[write]);
	arg[write] = NULL;*/
	return (0);
}
