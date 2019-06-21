/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <ktlili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 22:17:22 by ktlili            #+#    #+#             */
/*   Updated: 2019/06/20 17:36:57 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"

int		valid_env_char(char c)
{
	if ((ft_isalnum(c)) || (c == '_'))
		return (1);
	return (0);
}

int		valid_env_name(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (!valid_env_char(str[i]))
			return (0);
		i++;
	}
	if (i != ft_strlen(str))
		return (0);
	return (1);
}

char	*dget_env_value(char *name)
{
	if (!ft_strncmp("_", name, 1))
		return (g_sh.lastpara);	
	if (!ft_strncmp("?", name, 1))
		return (ft_itoa(g_sh.status));
	if (!ft_strncmp("#", name, 1))
		return (ft_itoa(ft_tablen(g_sh.av)));
	if (!ft_strncmp("*", name, 1))
		return (ft_ttos(g_sh.av, " "));
	if (!ft_strncmp("@", name, 1))
		return (ft_ttos(g_sh.av, " "));
	if (!ft_strcmp("-", name))
		return (NULL);
	if (!ft_strncmp("!", name, 1))
		return (ft_itoa(g_sh.lastback));
	if (!ft_strncmp("$", name, 1))
		return (ft_itoa(getpid()));
	if (ft_strisdigit(name) && ft_tablen(g_sh.av) > ft_atoi(name))
		return (ft_strdup(g_sh.av[ft_atoi(name)]));
	return (ft_strdup(get_env_value(name)));
}

char	*get_env_value(char *name)
{
	char *value;

	if ((value = varchr(g_sh.env, name)))
		return (value);
	if ((value = varchr(g_sh.local, name)))
		return (value);
	return (NULL);
}

int		set_shell_env(char *name, char *newvalue, int to_export)
{
	(void)to_export;
	if (!(g_sh.env = envaddstr(g_sh.env, name, newvalue)))
		return (MEMERR);
	return (0);
}
