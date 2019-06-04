/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_util_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <ktlili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:42:35 by ktlili            #+#    #+#             */
/*   Updated: 2019/06/04 17:50:30 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

int		get_ifs(char **ifs)
{
	const char *default_ifs = "  \t\n";

	if (!(*ifs = get_env_value("IFS")))
		*ifs = (char *)default_ifs;
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
	int				trunc;
	int				i;
	bool			brackets;
	const char		*valid = "-:=?";

	i = 1;
	trunc = 1;
	brackets = false;
	if (*(cursor + 1) == '{')
	{
		i++;
		trunc = 3;
		brackets = true;
	}
	while (parser_is_name_c(cursor[i])
	|| ((brackets) && (ft_cisin((char*)valid, cursor[i]))))
	{
		trunc++;
		i++;
	}
	i = ft_strlen(cursor + trunc);
	ft_memmove(cursor, cursor + trunc, ft_strlen(cursor + trunc));
	cursor[i] = 0;
}
