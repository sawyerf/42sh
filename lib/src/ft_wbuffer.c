/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wbuffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 22:18:14 by ktlili            #+#    #+#             */
/*   Updated: 2018/07/17 11:04:00 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		ft_ncpytobuff(char *str, unsigned int n)
{
	while (n)
	{
		ft_writebuff(*str, 0);
		str++;
		n--;
	}
	return (1);
}

int		ft_writebuff(char c, int print)
{
	static char	buffer[BUFF_SIZE];
	static int	index = 0;
	static int	wrote = 0;
	int			temp;

	if ((index == BUFF_SIZE) || ((print != 0) && (index > 0)))
	{
		write(1, buffer, index);
		index = 0;
		if (print)
		{
			temp = wrote;
			wrote = 0;
			return (temp);
		}
	}
	if (!print)
	{
		buffer[index] = c;
		index++;
		wrote++;
	}
	return (wrote);
}
