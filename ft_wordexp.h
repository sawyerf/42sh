/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordexp.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:39:07 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/13 01:04:05 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WORDEXP_H
# define FT_WORDEXP_H

#include "sh_core.h"
/* wordexp */
typedef struct s_str t_str;
typedef	struct	s_token t_token;
int	ft_wordexp(t_token *word);
int	handle_tilde(t_token *word);
int	handle_exp_param(t_token *word);
int	handle_field_split(t_token *word);
int	quote_removal(t_token *word);
int	insert_str(t_str *word, int *index, char *to_insert);

#endif
