/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:53:32 by juhallyn          #+#    #+#             */
/*   Updated: 2019/07/09 12:53:57 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"
#include "pwd.h"

int		tilde_valid(char c)
{
	if (ft_isalpha(c))
		return (1);
	if ((c == 0) || (c == '/') || (c == ':'))
		return (1);
	return (0);
}

size_t	count_dollars(char *str)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (*str == '$')
			count++;
		str++;
	}
	return (count);
}
