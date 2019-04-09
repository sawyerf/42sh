/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 14:16:02 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/09 20:34:51 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

static int		expand_redir(t_redir *redir)
{
	if ((redir->right) && (redir->right->type == HERE_END_QU))
		return (0);
	if ((redir->right) && (redir->right->type == HERE_END))
		return (ft_wordexp_heredoc(redir->right));
	if ((redir->left) && (ft_wordexp(redir->left, FT_TRUE) == MEMERR))
		return (MEMERR);
	if ((redir->right) && (ft_wordexp(redir->right, FT_TRUE) == MEMERR))
		return (MEMERR);
	return (0);
}

static void		handle_left(int *left_fd, t_redir *redir)
{
	if ((redir->op->type == GREAT) || (redir->op->type == GREATAND)
			|| (redir->op->type == DGREAT))
	{
		if (!redir->left)
			*left_fd = 1;
		else
			*left_fd = ft_atoi(redir->left->data.str);
		return ;
	}
	if (!redir->left)
		*left_fd = 0;
	else
		*left_fd = ft_atoi(redir->left->data.str);
}

static int		save_fd(int left_fd, t_list **head)
{
	t_list	*new;

	if (!(new = ft_lstnew(NULL, 0)))
		return (MEMERR);
	if (!(new->content = (int*)ft_memalloc(sizeof(int))))
		return (MEMERR);
	new->content_size = sizeof(int);
	*((int*)(new->content)) = left_fd;
	ft_lstadd(head, new);
	return (0);
}

int				apply_redir(t_redir *redir, t_list **head)
{
	int left_fd;
	int right_fd;
	int	ret;

	handle_left(&left_fd, redir);
	if ((ret = handle_right(&left_fd, &right_fd, redir)) == -1)
		return (-1);
	else if (ret == 1)
		return (0);
	if (check_fd(right_fd) == FT_FALSE)
		return (-1);
	if ((head) && (save_fd(left_fd, head)))
		return (MEMERR);
	if (dup2(right_fd, left_fd) == -1)
	{
		ft_dprintf(STDERR_FILENO, "21sh: FATAL ERROR dup2 fuckd up\n");
		return (-1);
	}
	if ((redir->op->type != GREATAND) && (redir->op->type != LESSAND))
		close(right_fd);
	return (0);
}

int				handle_redir(t_redir *redir_lst, t_list **head)
{
	t_redir *iter;
	int		ret;

	iter = redir_lst;
	while (iter)
	{
		if (expand_redir(iter))
			return (MEMERR);
		if ((iter->op->type == DLESS)
			|| (iter->right->data.str[0] != 0))
		{
			if ((ret = apply_redir(iter, head)))
				return (ret);
		}
		else
		{
			ft_dprintf(STDERR_FILENO,
				"21sh: ambiguous redir: filename expands to empty string\n");
			return (-1);
		}
		iter = iter->next;
	}
	return (0);
}
