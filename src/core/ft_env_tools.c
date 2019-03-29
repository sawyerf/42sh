/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 22:48:33 by ktlili            #+#    #+#             */
/*   Updated: 2019/03/29 21:50:03 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

char	*get_value(char *env_var)
{
	int i;

	i = 0;
	while (valid_env_char(env_var[i]))
		i++;
	if (env_var[i] == 0)
		return (env_var + i);
	return (env_var + i + 1);
}

int		valid_env_var(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

void	print_env_tab(char **tab)
{
	int i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		ft_printf("%s\n", tab[i]);
		i++;
	}
}
