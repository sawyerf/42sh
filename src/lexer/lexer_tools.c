/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:35:55 by ktlili            #+#    #+#             */
/*   Updated: 2019/05/02 11:19:05 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

int		str_putnstr(char *str, t_str *data, size_t n)
{
	while (*str && n)
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

	if (!data->str || data->len <= data->size + 1)
	{
		if (!data->str)
		{
			data->size = 0;
			data->len = 0;
			data->str = NULL;
		}
		if (ft_str_realloc(data, INPUTSZ) == MEMERR)
			return (MEMERR);
	}
	i = data->len;
	data->str[i] = **c;
	*c = *c + 1;
	data->len = i + 1;
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
