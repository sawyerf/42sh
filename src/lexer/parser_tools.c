/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/12 23:14:47 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_lexer.h"


static	void	add_to_lst(t_token *to_add, t_token **head)
{
	t_token *tmp;

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

int	add_redir_lst(t_redir *to_add, t_redir **head)
{
	t_redir *tmp;
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

int		build_cmd(t_token *to_add, t_simple_cmd *cmd)
{
	t_token *tmp;

	if (!(tmp = dup_token(to_add)))
		return (MEMERR);
	if (to_add->type == WORD)
		add_to_lst(tmp, &(cmd->word_lst));
	else if (to_add->type == ASSIGN)
		add_to_lst(tmp, &(cmd->assign_lst));
	return (0);
}

int	build_redir(t_token *to_add, t_redir *redir)
{
	t_token *tmp;

	if (!(tmp = dup_token(to_add)))
		return (MEMERR);
	if (to_add->type == IO_NUM)
		redir->left = tmp;	
	else if ((to_add->type >= LESSAND) && (to_add->type <= GREAT))
		redir->op = tmp;
	else if (to_add->type == FILENAME)
		redir->right = tmp;
	return (0);
}


int	add_to_pipeline(t_parser *parser)
{
	t_simple_cmd *tmp;
	t_simple_cmd *iter;

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

void	print_redir_lst(t_redir *start)
{
	while (start)
	{
		ft_printf("left:");
		print_token(start->left);
		ft_printf("op:\n");
		print_tokens(start->op);
		ft_printf("right\n");
		print_tokens(start->right);
		ft_printf("==========================================\n");
		start = start->next;
	}
}

void	test_simplecmd(t_simple_cmd *cmd)
{
	ft_printf(">>>>>>SIMPLE COMMAND============\n");
	ft_printf("args_lst:\n");
	print_tokens(cmd->word_lst);
	ft_printf("***************************\n");
	ft_printf("assign_lst:\n");
	print_tokens(cmd->assign_lst);
	ft_printf("***************************\n");
	ft_printf("redir_lst:\n");
	print_redir_lst(cmd->redir_lst);
	ft_printf(">>>>>>END OF SIMPLE COMMAND======\n");
}
void	test_pipeline(t_parser *parser)
{
	t_simple_cmd *start;

	start = parser->pipeline;
	while (start)
	{
		test_simplecmd(start);
		start=  start->next;

	}
}
/*
void	build_cmd(t_token *to_add, t_simple_cmd *cmd)
{
	if (to_add->type == WORD)
	{
		if (!cmd->cmd_name)
			cmd->cmd_name = to_add;
		else
			add_to_lst(to_add, &(cmd->args_lst))
		to_add->next = NULL;	
	}
	else if (to_add->type == ASSIGN)
	{
		add_to_lst(to_add, &(cmd->assign_lst));
		to_add = NULL;
	}
}*/
