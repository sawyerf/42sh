/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:16:16 by apeyret           #+#    #+#             */
/*   Updated: 2019/07/06 16:55:29 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
			if (write(STDOUT_FILENO, cmd->av[i],
				ft_strlen(cmd->av[i])) == -1)
			{
				ft_dprintf(STDERR_FILENO, "42sh: echo: fd error\n");
				return (1);
			}
			i++;
			if (cmd->av[i] != NULL)
				ft_printf(" ");
		}
	}
	if ((cmd->av[1] && ft_strcmp(cmd->av[1], "-n")) || !cmd->av[1])
		ft_printf("\n");
	return (0);
}
