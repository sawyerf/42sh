/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:35:55 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/09 21:31:41 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

int		str_putnstr(char *str, t_str *data, size_t n)
{
	while ((*str) && (n))
	{
		n--;
		if (str_putc(&str, data) == MEMERR)
			return (MEMERR);
	}
	return (0);
}

int		str_putc(char **c, t_str *data)
{
	size_t i;

	i = data->len;
	data->str[i] = **c;
	*c = *c + 1;
	data->len = i + 1;
	if (data->len == data->size)
		if (ft_str_realloc(data, INPUTSZ) == MEMERR)
			return (MEMERR);
	return (0);
}

int		ft_is_whitespace(char c)
{
	static char	*ws = "\n\t ";
	int			i;

	i = 0;
	while (ws[i])
	{
		if (ws[i] == c)
			return (1);
		i++;
	}
	return (0);
}
