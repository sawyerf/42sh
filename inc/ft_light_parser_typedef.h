/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_parser_typedef.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:02:34 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/06 20:26:10 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIGHT_PARSER_TYPEDEF_H
# define FT_LIGHT_PARSER_TYPEDEF_H

typedef enum	e_expecting
{
	cmd_name,
	arg,
	param,
}				t_expecting;

typedef struct	s_autocomplete
{
	char		*str;
	t_expecting type;
}				t_autocomplete;

#endif
