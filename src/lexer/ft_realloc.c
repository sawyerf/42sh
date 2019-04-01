/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:31:39 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/01 13:31:40 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

int		ft_str_realloc(t_str *str_st, size_t newsz)
{
	char *ptr;

	if (newsz == 0)
		return (0);
	if (!(ptr = ft_memalloc(str_st->size + newsz)))
		return (MEMERR);
	ft_memcpy(ptr, str_st->str, str_st->size);
	str_st->size = str_st->size + newsz;
	free(str_st->str);
	str_st->str = ptr;
	return (0);
}
