/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 14:16:02 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/01 13:22:15 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

/*
** to do:
** builtin should exit when redir fail, command should continue
** fstat fd before dup ?
*/

static int		expand_redir(t_redir *redir)
{
	if ((redir->right) && (redir->right->type == HERE_END_QU))
		return (0);
	if ((redir->left) && (ft_wordexp(redir->left, FT_TRUE) == MEMERR))
		return (MEMERR);
	if ((redir->right) && (ft_wordexp(redir->right, FT_TRUE) == MEMERR))
		return (MEMERR);
	return (0);
}

static t_bool	check_fd(int fd)
{
	static int	t = 0;
	struct stat	buf;

	if (!fstat(fd, &buf))
		return (FT_TRUE);
	ft_dprintf(STDERR_FILENO, "21sh: bad file descriptor: %d\n", fd);
	t++;
	return (FT_FALSE);
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
		// case of >&- we close fd we dont use dup2
	if (check_fd(right_fd) == FT_FALSE)
		return (-1);
		// maybe return 0 ?
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
		// second condition to prevent \0 filename open
		{
			if ((ret = apply_redir(iter, head)))
			{
				ft_dprintf(STDERR_FILENO, "failed redir %d\n", ret);
				return (ret);
			}
		}
		else
			ft_dprintf(STDERR_FILENO, "ambiguous redir, null right\n");
		iter = iter->next;
	}
	return (0);
}
