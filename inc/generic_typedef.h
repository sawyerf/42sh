/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_typedef.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/06 19:20:19 by apeyret          ###   ########.fr       */
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
;
typedef enum e_bool
{
	FT_FALSE = 0,
	FT_TRUE = 1,
}			t_bool;

#endif
