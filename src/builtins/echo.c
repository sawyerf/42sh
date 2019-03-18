/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:16:16 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/18 15:16:32 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

int	ft_echo(t_cmd_tab *cmd)
{
	int i;

	if (cmd->av[1] != NULL)
	{
		i = 1;
		while (cmd->av[i] != NULL)
		{
			ft_printf("%s", cmd->av[i]);
			i++;
			if (cmd->av[i] != NULL)
				ft_printf(" ");
		}
	}
	ft_printf("\n");
	return (0);
}
