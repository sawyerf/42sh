/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 11:48:18 by ktlili            #+#    #+#             */
/*   Updated: 2019/03/19 14:16:27 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

int	eval_tree(t_ast_node *tree)
{
	if (tree == NULL)
	{
		ft_printf("fatal error in eval_tree: unknown node type\n");
		return (-1); // this has to change
	}
	if ((tree->type == SEMI_COL) || (tree->type == AMPERS)
		|| (tree->type == NEWLINE))
	{
		
		if (tree->left)
			eval_tree(tree->left);
		if (tree->right)
			eval_tree(tree->right);
		return (0);
	}
	else if (tree->type == AND_IF)
	{
		eval_tree(tree->left);
		if (tree->left->exit_status == 0)
		{
			eval_tree(tree->right);
			tree->exit_status = tree->right->exit_status;
		}
		return (0);
	}
	else if (tree->type == OR_IF)
	{
		eval_tree(tree->left);
		if (tree->left->exit_status != 0)
		{
			eval_tree(tree->right);
			tree->exit_status = tree->right->exit_status;	
		}
		else
			tree->exit_status = tree->left->exit_status;
		return (0);
	}
	else if (tree->type == PIPE)
	{
		exec_pipeline(tree);
		return (0);
	}
	ft_printf("fatal error in eval_tree: unknown node type\n");
	exit(1);
}
