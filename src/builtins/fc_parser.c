/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:07:04 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/26 14:50:12 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

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
	fc->range[0] = 0;
	fc->range[1] = 0;
}

int		fc_parser(char **av, t_fc *fc)
{
	char	c;
	int		i;

	av++;	
	c = 0;
	fc_init(fc);
	while (*av)
	{
		if (!ft_strcmp(*av, "--") || **av != '-' || ft_strisdigit(*av))
		{
			if (!ft_strcmp(*av, "--"))
				av++;
			break;
		}
		i = 1;
		while ((*av)[i])
		{
			if (ft_cisin("elnrs", (*av)[i]))
			{
				if (!ft_cisin(fc->opt, (*av)[i]))
					ft_strncat(fc->opt, *av + i, 1);
				c = (*av)[i];
			}
			else
			{
				ft_dprintf(2, "fc: -%c: invalid option\n", (*av)[i]);
				return (-1);
			}
			i++;
		}
		if (c == 'e')
		{
			av++;
			if (!*av)
			{
				ft_dprintf(2, "fc: -e: option requires an argument\n");
				ft_dprintf(2, "fc: usage: fc [-e ename] [-nlr] [first] [last]");
				return (-1);
			}
			fc->editor = ft_strdup(*av);
			av++;
			c = 0;
			continue ;
		}
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
	//fc_pprint(fc);
	return (0);
}
