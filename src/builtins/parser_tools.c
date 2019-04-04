/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:27:49 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/04 15:29:34 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		parser_takeopt(char *opt, char *arg, char *in, char *name)
{
	int		i;
	char	c;

	i = 1;
	while (arg[i])
	{
		c = arg[i];
		if (!ft_cisin(in, arg[i]))
		{
			if (ft_cisin(opt, arg[i]))
				ft_strncat(in, arg + i, 1);
			else
			{
				ft_dprintf(2, "%s: -%c: invalid option\n", name, arg[i]);
				//ft_dprintf(2, "usage: hash [-r] [name ...]\n");
				//ft_dprintf(2, \
				//"fc: usage: fc [-e ename] [-nlr] [first] [last]\n");
				return (0);
			}
		}
		i++;
	}
	return (c);
}
