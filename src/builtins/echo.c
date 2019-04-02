/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:16:16 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/02 18:06:30 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

int	ft_echo(t_cmd_tab *cmd)
{
	int i;

	if (cmd->av[1] != NULL)
	{
		i = 1;
		if (!ft_strcmp(cmd->av[1], "-n"))
			i = 2;
		while (cmd->av[i] != NULL)
		{
			ft_printf("%s", cmd->av[i]);
			i++;
			if (cmd->av[i] != NULL)
				ft_printf(" ");
		}
	}
	if ((cmd->av[1] && ft_strcmp(cmd->av[1], "-n")) || !cmd->av[1])
		ft_printf("\n");
	return (0);
}
