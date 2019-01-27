/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_buff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 23:05:01 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/12 23:10:59 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sh_core.h"

int	write_dbuff(t_list *buffer, char c, int *index)
{
	char			*tmp;
	static size_t	buff_size = 1024;

	if (*index >= (int)buffer->content_size)
	{
		tmp = ft_memalloc(1 + buffer->content_size + buff_size);
		if (tmp == NULL)
			return (-1);
		buffer->content_size = buffer->content_size + buff_size;
		ft_strcpy(tmp, buffer->content);
		free(buffer->content);
		buffer->content = tmp;
	}
	((char*)buffer->content)[*index] = c;
	*index = *index + 1;
	return (0);
}

int	putstr_dbuff(t_list *buffer, char *str, int *index)
{
	while (*str)
	{
		if (write_dbuff(buffer, *str, index) != 0)
			return (-1);
		str++;
	}
	return (0);
}
