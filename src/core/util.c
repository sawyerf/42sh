/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 16:10:23 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/04 16:13:43 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

int			add_slash(char **path)
{
	int		len;
	char	*tmp;

	len = ft_strlen(*path);
	if ((len != 0) && ((*path)[len - 1] != '/'))
	{
		if (!(tmp = ft_strjoin(*path, "/")))
			return (MEMERR);
		ft_strdel(path);
		*path = tmp;
	}
	return (0);
}

int			ft_cmptab(char **tab, char *str)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		if (!ft_strcmp(tab[i], str))
			return (i);
		i++;
	}
	return (-1);
}

static void	state_unquoted(char *line, t_quote_state *state)
{
	*state = (*line == '"') ? in_dquote : *state;
	*state = (*line == '\'') ? in_squote : *state;
	*state = (*line == '\\') ? backslash : *state;
}

static int	state_backslash(char **line, t_quote_state *state,
		t_quote_state save)
{
	if (**line == '\n' && *((*line) + 1) == '\0')
		return (-1);
	*line = *line + 1;
	*state = save;
	return (0);
}

int			missing_quote(char *line)
{
	t_quote_state state;
	t_quote_state save;

	state = unquoted;
	while (*line)
	{
		save = state;
		if (state == unquoted)
			state_unquoted(line, &state);
		else if (state == in_dquote)
		{
			state = (*line == '"') ? unquoted : state;
			state = (*line == '\\') ? backslash : state;
		}
		else if (state == in_squote)
			state = (*line == '\'') ? unquoted : state;
		line++;
		if (state == backslash)
			if (state_backslash(&line, &state, save))
				return (-1);
	}
	if (state != unquoted)
		return (-1);
	return (0);
}
