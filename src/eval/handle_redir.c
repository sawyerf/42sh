/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 14:16:02 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/06 19:24:07 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"
#include <fcntl.h>


int expand_redir(t_redir *redir)
{
	if ((redir->left) && (ft_wordexp(redir->left, FT_TRUE) == MEMERR))
		return (MEMERR);
	if ((redir->right) && (ft_wordexp(redir->right, FT_TRUE) == MEMERR))
		return (MEMERR);
	return (0);
}

int	apply_redir(t_redir *redir)
{
	int to;
	int from;
	if (redir->op->type == GREAT)
	{
		if (!redir->left)
			from = 1;
		else	
			from = ft_atoi(redir->left->data.str);	
		to = open(redir->right->data.str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (to == -1)
		{
			write(2, "failed opening file\n", 19);
			return (0);
		}
		dup2(from, to);
	//	dup2(1, 2);
	}
	else if (redir->op->type == GREATAND)
	{

	}
	return (0);
}


int	handle_redir(t_redir *redir_lst)
{
	t_redir *iter;

	iter = redir_lst;
	while (iter)
	{
		if (expand_redir(iter))
			return (MEMERR);
		if (apply_redir(iter) == MEMERR)
			return (MEMERR);
		iter = iter->next;
	}
	return (0);
	
}
