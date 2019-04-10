/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_parser.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:19:04 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/10 18:19:13 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIGHT_PARSER_H
# define FT_LIGHT_PARSER_H

# include "sh_core.h"
# include "ft_lexer.h"
# include "ft_eval.h"

int		ft_light_parser(char *line, t_autocomplete *autocomplete);
void	clear_autocom(t_autocomplete *autoc);
#endif
