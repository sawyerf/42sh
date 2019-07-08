/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmdline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 19:53:39 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 19:55:32 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

char	*make_cmdline(t_token *start, t_token *end, int last)
{
	char	*ln;
	size_t	tot_len;
	t_token	*iter;

	tot_len = 0;
	iter = start;
	while (iter)
	{
		tot_len += ft_strlen(iter->data.str) + 1;
		if (iter == end)
			break ;
		iter = iter->next;
	}
	if (!(ln = ft_strnew(tot_len)))
		return (NULL);
	iter = start;
	while (iter)
	{
		ft_strcat(ln, iter->data.str);
		if ((iter == end) || (((iter = iter->next) == end) && !last))
			break ;
		ft_strcat(ln, " ");
	}
	return (ln);
}
