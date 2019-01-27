/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/12 20:21:49 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sh_core.h"

static int	init_dbuff(t_list *buffer, char *line)
{
	buffer->content = ft_strnew(ft_strlen(line));
	if (buffer->content == NULL)
		return (MEMERR);
	buffer->content_size = ft_strlen(line);
	return (0);
}

char		*expand_dollar(char *line)
{
	t_list	buffer;
	char	*e_var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (init_dbuff(&buffer, line) != 0)
		return (NULL);
	while (line[i] != 0)
	{
		if ((line[i] == '$') && (line[i + 1] != 0))
		{
			e_var = get_env_value(&line[i + 1]);
			if (((e_var != NULL) && (*e_var != 0))
				&& (putstr_dbuff(&buffer, e_var, &j) != 0))
				return (NULL);
			while (valid_env_char(line[i + 1]))
				i++;
		}
		else if (write_dbuff(&buffer, line[i], &j) != 0)
			return (NULL);
		i++;
	}
	return (buffer.content);
}
