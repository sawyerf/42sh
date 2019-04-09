/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:51:15 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/09 21:07:32 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Ft_light_parser_H
# define Ft_light_parser_H

# include "sh_core.h"
# include "ft_lexer.h"
# include "ft_eval.h"

int		ft_light_parser(char *line, t_autocomplete *autocomplete);
void	clear_autocom(t_autocomplete *autoc);
#endif
