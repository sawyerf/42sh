/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 09:26:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/05/27 16:44:36 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

void	dispatch_parse_err(int error)
{
	if (error == 1)
	{
		ft_printf("21sh: malloc error\n");
		exit(1);
	}
	else if (error == 2)
		ft_printf("21sh: syntax error\n");
}

void	putstr_stderr(char *str)
{
	int len;

	len = ft_strlen(str);
	write(2, str, len);
}

void	free_tab_bytes(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
