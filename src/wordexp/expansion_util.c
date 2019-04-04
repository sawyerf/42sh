/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/01 12:31:01 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

int	next_bslash(char *str, int index)
{
	if ((str[index + 1] != '\0'))
		return (index + 1);
	return (index);
}

int	next_squote(char *str, int index)
{
	index++;
	while ((str[index] != 0) && (str[index] != '\''))
		index++;
	return (index);
}

int	next_dquote(char *str, int index)
{
	index++;
	while (str[index] != 0)
	{
		if ((str[index] == '"') && (str[index - 1] != '\\'))
			break ;
		index++;
	}
	return (index);
}
