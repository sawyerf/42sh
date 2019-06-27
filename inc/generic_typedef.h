/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_typedef.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:23:40 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/10 18:24:10 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERIC_TYPEDEF_H
# define GENERIC_TYPEDEF_H

typedef	struct	s_str
{
	char	*str;
	size_t	size;
	size_t	len;
}				t_str;

typedef enum	e_bool
{
	FT_FALSE = 0,
	FT_TRUE = 1,
}				t_bool;

#endif
