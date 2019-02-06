/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_typedef.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/04 15:31:10 by ktlili           ###   ########.fr       */
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
	FALSE = 0,
	TRUE = 1,
}			t_bool;

#endif
