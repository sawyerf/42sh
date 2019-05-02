/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_util_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:42:35 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/09 21:45:20 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

int		get_ifs(char **ifs)
{
	static char *default_ifs = "  \t\n";

	if (!(*ifs = get_env_value("IFS")))
		*ifs = default_ifs;
	else
	{
		if (!(*ifs = expand_ifs(*ifs)))
			return (MEMERR);
		if (*ifs == 0)
		{
			free(*ifs);
			*ifs = NULL;
		}
	}
	return (0);
}

void	delete_varname(char *cursor)
{
	int		trunc;
	int		i;

	i = 1;
	trunc = 1;
	if (*(cursor + 1) == '{')
	{
		i++;
		trunc = 3;
	}
	while (parser_is_name_c(cursor[i]))
	{
		trunc++;
		i++;
	}
	i = ft_strlen(cursor + trunc);
	ft_memmove(cursor, cursor + trunc, ft_strlen(cursor + trunc));
	cursor[i] = 0;
	return ;
}
