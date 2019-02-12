/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 14:16:02 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/08 15:45:10 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"
#include <fcntl.h>
/*
 * to do:
 * check >& and <& t_redir->right for ambiguous redir
 * figure out why 'ls >& toto' is returning -1
 *
 */

static int expand_redir(t_redir *redir)
{
	if ((redir->left) && (ft_wordexp(redir->left, FT_TRUE) == MEMERR))
		return (MEMERR);
	if ((redir->right) && (ft_wordexp(redir->right, FT_TRUE) == MEMERR))
		return (MEMERR);
	return (0);
}

/*
 * <&WORD and >&WORD where word is not digits should be rejected here 
 */

static int	get_open_flags(t_token_type op)
{
	if (op == GREAT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (op == DGREAT)
		return (O_WRONLY | O_APPEND | O_CREAT);
	return (O_RDONLY);
}

static t_bool check_fd(int fd)
{
	struct stat buf;

	ft_printf("right fd: %d\n", fd);
	if (!fstat(fd, &buf))
		return (FT_TRUE);
	ft_printf("21sh: bad file descriptor: %d\n", fd);
	return (FT_FALSE);
}




int apply_redir(t_redir *redir)
{
	int left_fd;
	int right_fd;
	int oflag;

	if ((redir->op->type == GREAT) || (redir->op->type == GREATAND) || (redir->op->type == DGREAT))
	{
		if (redir->left == NULL)
			left_fd = 1;	
	}
	else 
	{
		if (redir->left == NULL)
			left_fd = 0;
	}	
	if ((redir->op->type == GREATAND) || (redir->op->type == LESSAND))
	{
		left_fd = ft_atoi(redir->left->data.str);
		right_fd = ft_atoi(redir->right->data.str);
	}
	else
	{
		oflag = get_open_flags(redir->op->type);
		right_fd = open(redir->right->data.str, oflag, 0644); 
		if (right_fd == -1)
		{
			ft_printf("Error opening %s\n", redir->right->data.str);
			return (0);
		}
	}
	if (check_fd(right_fd) == FT_FALSE)
		return (-1);
	dup2(right_fd, left_fd);
	return (0);
}

int	handle_redir(t_redir *redir_lst)
{
	t_redir *iter;
	int		ret;

	iter = redir_lst;
	while (iter)
	{
		if (expand_redir(iter))
			return (MEMERR);
		if ((ret = apply_redir(iter)))
			return (ret);
		iter = iter->next;
	}
	return (0);
	
}
