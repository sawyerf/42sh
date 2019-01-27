/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordexp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/12 20:21:49 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_wordexp.h"


int	ft_wordexp(t_token *word)
{
	if (handle_tilde(word) == MEMERR)
		return (MEMERR);

//	ft_printf("=========\nbefore exp\n==============\n");
//	print_token(word);
//	ft_printf("=============================================\n");
	if (handle_exp_param(word) == MEMERR)
		return (MEMERR);
	if (handle_field_split(word) == MEMERR)
		return (MEMERR);
	if (quote_removal(word) == MEMERR)
		return (MEMERR);
return (0);
}
