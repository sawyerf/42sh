/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_util_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <ktlili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:42:35 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/09 17:32:03 by ktlili           ###   ########.fr       */
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

void	init_vars(char *cursor, int *i, int *trunc, bool *brackets)
{
	if (*(cursor + 1) == '{')
	{
		(*i)++;
		*trunc = 3;
		*brackets = true;
	}
}

void	delete_varname(char *cursor)
{
	int				trunc;
	int				i;
	bool			brackets;
	const char		*valid = "#-:=?+*%/[]!.";

	i = 1;
	trunc = 1;
	brackets = false;
	init_vars(cursor, &i, &trunc, &brackets);
	if (ft_cisin("@*$#?", cursor[i]))
		trunc++;
	while (parser_is_name_c(cursor[i]) || (ft_cisin((char*)valid, cursor[i]))
			|| ((brackets) && (cursor[i])))
	{
		if ((cursor[i] == '}')
				|| ((!brackets) && (ft_cisin((char*)valid, cursor[i]))))
			break ;
		trunc++;
		i++;
	}
	i = ft_strlen(cursor + trunc);
	ft_memmove(cursor, cursor + trunc, ft_strlen(cursor + trunc));
	cursor[i] = 0;
}
