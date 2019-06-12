/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free_fn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:08:10 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/09 21:08:40 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "readline.h"

void	free_redir(t_redir *redir)
{
	if (redir->left)
		free_token(redir->left);
	if (redir->right)
		free_token(redir->right);
	if (redir->op)
		free_token(redir->op);
	ft_bzero(redir, sizeof(t_redir));
}

void	free_redir_lst(t_redir *redir)
{
	t_redir *tmp;

	while (redir)
	{
		tmp = redir->next;
		free_redir(redir);
		free(redir);
		redir = tmp;
	}
}

void	free_simple_cmd(t_simple_cmd *cmd)
{
	if (cmd->word_lst)
		free_token_lst(cmd->word_lst);
	if (cmd->assign_lst)
		free_token_lst(cmd->assign_lst);
	if (cmd->redir_lst)
		free_redir_lst(cmd->redir_lst);
	ft_bzero(cmd, sizeof(t_simple_cmd));
}

void	free_pipeline(t_simple_cmd *pipeline)
{
	t_simple_cmd *tmp;

	while (pipeline)
	{
		tmp = pipeline->next;
		free_simple_cmd(pipeline);
		free(pipeline);
		pipeline = tmp;
	}
}

void	free_tree(t_ast_node *tree)
{
	if (tree == NULL)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	if (tree->pipeline)
		free_pipeline(tree->pipeline);
	free(tree);
}
