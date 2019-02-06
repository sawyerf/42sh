/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:51:15 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/02 16:55:41 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Ft_light_parser_H
# define Ft_light_parser_H

# include "sh_core.h"
# include "ft_lexer.h"
# include "ft_eval.h"

/*
recursive decent functions 

int	lp_expect_linebreak(t_light_parser *parser);
int	lp_expect_separator_op(t_light_parser *parser);
int	lp_expect_separator(t_light_parser *parser);
int	lp_expect_filename(t_light_parser *parser);
int	lp_expect_io_file(t_light_parser *parser);
int	lp_expect_io_redir(t_light_parser *parser);
int	lp_expect_assign(t_light_parser *parser);
int	lp_expect_cmd_pre(t_light_parser *parser);
int	lp_expect_word(t_light_parser *parser);
int	lp_expect_cmd_suffix(t_light_parser *parser);
int	lp_expect_cmd_name(t_light_parser *parser);
int	lp_expect_simeple_cmd(t_light_parser *parser);
int	lp_expect_pipeline_suffix(t_light_parser *parser);
int	lp_expect_pipeline(t_light_parser *parser);
int	lp_expect_and_or_suffix(t_light_parser *parser);
int	lp_expect_and_or(t_light_parser *parser);
int	lp_expect_list_suffix(t_light_parser *parser);
int	lp_expect_list(t_light_parser *parser);
int	lp_expect_complete_cmd(t_light_parser *parser);


t_light_parser light_parser(char *line);
*/
int		ft_light_parser(char *line, t_autocomplete *autocomplete);

#endif
