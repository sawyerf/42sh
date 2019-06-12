/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/01 15:41:59 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

void	add_to_lst(t_token *to_add, t_token **head)
{
	t_token	*tmp;

	if (*head == NULL)
		*head = to_add;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = to_add;
	}
}

int		build_cmd(t_token *to_add, t_simple_cmd *cmd)
{
	t_token	*tmp;

	if (!(tmp = dup_token(to_add)))
		return (MEMERR);
	if ((to_add->type == WORD) || (to_add->type == ASSIGN))
		add_to_lst(tmp, &(cmd->word_lst));
	return (0);
}

int		build_redir(t_token *to_add, t_redir *redir)
{
	t_token	*tmp;

	if (!(tmp = dup_token(to_add)))
		return (MEMERR);
	if (to_add->type == IO_NUM)
		redir->left = tmp;
	else if ((to_add->type >= LESSAND) && (to_add->type <= DLESS))
		redir->op = tmp;
	else if ((to_add->type == FILENAME) || (to_add->type == HERE_END)
		|| (to_add->type == HERE_END_QU))
		redir->right = tmp;
	return (0);
}

int		add_to_pipeline(t_parser *parser)
{
	t_simple_cmd	*tmp;
	t_simple_cmd	*iter;

	if (!(tmp = ft_memalloc(sizeof(t_simple_cmd))))
		return (MEMERR);
	ft_memcpy(tmp, &(parser->cmd), sizeof(t_simple_cmd));
	if (parser->pipeline == NULL)
		parser->pipeline = tmp;
	else
	{
		iter = parser->pipeline;
		while (iter->next)
			iter = iter->next;
		iter->next = tmp;
	}
	return (0);
}

int		add_redir_lst(t_redir *to_add, t_redir **head)
{
	t_redir	*tmp;
	t_redir	*iter;

	if (!(tmp = ft_memalloc(sizeof(t_redir))))
		return (MEMERR);
	ft_memcpy(tmp, to_add, sizeof(t_redir));
	if (*head == NULL)
		*head = tmp;
	else
	{
		iter = *head;
		while (iter->next)
			iter = iter->next;
		iter->next = tmp;
	}
	return (0);
}
