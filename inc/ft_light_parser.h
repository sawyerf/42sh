/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_parser.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:19:04 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 19:47:38 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIGHT_PARSER_H
# define FT_LIGHT_PARSER_H

# include "sh_core.h"
# include "ft_lexer.h"
# include "ft_eval.h"
# include <stdbool.h>

int		ft_light_parser(char *line, t_autocomplete *autocomplete);
t_token	*get_last_tk(t_token *t, bool *first_word);
#endif
