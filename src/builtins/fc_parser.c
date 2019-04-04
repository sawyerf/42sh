/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:07:04 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/04 15:28:43 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	fc_pprint(t_fc *fc)
{
	ft_printf("opt:       %s\n", fc->opt);
	ft_printf("editor:    %s\n", fc->editor);
	ft_printf("range[0]:  %s\n", fc->range[0]);
	ft_printf("range[1]:  %s\n", fc->range[1]);
}

void	fc_init(t_fc *fc)
{
	ft_bzero(fc->opt, 6);
	fc->editor = NULL;
	fc->to = NULL;
	fc->by = NULL;
	fc->range[0] = 0;
	fc->range[1] = 0;
}

int		fc_parsertr(char ***av, t_fc *fc)
{
	char	c;

	while (**av)
	{
		if (!ft_strcmp(**av, "--") || ***av != '-' || ft_strisdigit(**av))
		{
			if (!ft_strcmp(**av, "--"))
				(*av)++;
			return (0);
		}
		if (!(c = parser_takeopt("elnrs", **av, fc->opt, "fc")))
			return (-1);
		if (c == 'e')
		{
			(*av)++;
			if (!**av)
				return (ft_rperr(-1, "fc: -e: option requires an argument\n"));
			if (!(fc->editor = ft_strdup(**av)))
				return (MEMERR);
			c = 0;
		}
		(*av)++;
	}
	return (0);
}

int		fc_parser(char **av, t_fc *fc)
{
	int		i;

	av++;
	fc_init(fc);
	if (fc_parsertr(&av, fc) < 0)
		return (-1);
	if (*av && ft_cisin(fc->opt, 's') && ft_cisin(*av, '='))
	{
		if (!(fc->to = ft_strndup(*av, ft_strnext(*av, "=")))
			|| !(fc->by = ft_strdup(*av + ft_strnext(*av, "=") + 1)))
			return (-1);
		av++;
	}
	i = 0;
	while (*av)
	{
		if (i < 2)
		{
			if (!(fc->range[i] = ft_strdup(*av)))
				return (MEMERR);
			i++;
		}
		av++;
	}
	return (0);
}
