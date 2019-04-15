/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atcpl_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 21:46:28 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/15 21:47:23 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char	cmdisin(char *cmd)
{
	char	c;

	while (*cmd)
	{
		if (*cmd == '\\')
		{
			if (!cmd[1])
				return ('\\');
			cmd += 2;
		}
		if (ft_cisin("'\"", *cmd))
		{
			c = *cmd;
			cmd++;
			while (*cmd != c)
			{
				if (!*cmd)
					return (c);
				if (*cmd == '\\' && cmd[1])
					cmd++;
				cmd++;
			}
		}
		cmd++;
	}
	return (0);
}

int		cmdisincurs(t_rdl *rdl)
{
	char	c;
	char	ret;

	c = rdl->str[rdl->curs];
	ret = cmdisin(rdl->str);
	rdl->str[rdl->curs] = c;
	return (ret);
}
