/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 22:48:33 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/01 14:08:34 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

static int		merge_env(char **new_env, char *to_add)
{
	int len;

	len = 0;
	while (valid_env_char(to_add[len]))
		len++;
	while (*new_env != NULL)
	{
		if (!ft_strncmp(*new_env, to_add, len))
		{
			free(*new_env);
			*new_env = ft_strdup(to_add);
			if (*new_env == NULL)
				return (MEMERR);
			return (0);
		}
		new_env++;
	}
	return (-1);
}

int				append_tab(char **new_env, char **to_add, int count)
{
	int i;
	int ret;

	i = 0;
	while (new_env[i] != NULL)
		i++;
	while (count)
	{
		if ((ret = merge_env(new_env, *to_add)) == -1)
		{
			new_env[i] = ft_strdup(*to_add);
			if (new_env[i] == NULL)
				return (MEMERR);
			i++;
		}
		if (ret == MEMERR)
			return (MEMERR);
		count--;
		to_add++;
	}
	new_env[i] = NULL;
	return (0);
}

int				valid_env_var(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

void			print_tab(char **tab)
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
