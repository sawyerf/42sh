/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:27:49 by apeyret           #+#    #+#             */
/*   Updated: 2019/07/08 15:30:40 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		invalid_option(char *name, char arg, char *opt)
{
	ft_dprintf(2, "%s: -%c: invalid option\n", name, arg);
	ft_dprintf(2, "usage: %s [-%s]\n", name, opt);
	return (0);
}

int		parser_takeopt(char *opt, char *arg, char *in, char *name)
{
	int		i;
	char	c;

	i = 1;
	c = 0;
	if (!ft_strcmp(arg, "--"))
		return ('-' * -1);
	if (*arg != '-')
		return (-1);
	while (arg[i])
	{
		c = arg[i];
		if (!ft_cisin(in, arg[i]))
		{
			if (ft_cisin(opt, arg[i]))
				ft_strncat(in, arg + i, 1);
			else
				return (invalid_option(name, arg[i], opt));
		}
		i++;
	}
	return (c);
}
