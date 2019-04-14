/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 11:48:18 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/09 19:52:21 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

static int	eval_sep(t_ast_node *tree)
{
	if ((tree->left) && (eval_tree(tree->left) == MEMERR))
		return (MEMERR);
	if ((tree->right) && (eval_tree(tree->right) == MEMERR))
		return (MEMERR);
	return (0);
}

static int	eval_and_if(t_ast_node *tree)
{
	if (eval_tree(tree->left) == MEMERR)
		return (MEMERR);
	if (tree->left->exit_status == 0)
	{
		if (eval_tree(tree->right) == MEMERR)
			return (MEMERR);
		tree->exit_status = tree->right->exit_status;
	}
	else
		tree->exit_status = tree->left->exit_status;
	return (0);
}

static int	eval_or_if(t_ast_node *tree)
{
	if (eval_tree(tree->left) == MEMERR)
		return (MEMERR);
	if (tree->left->exit_status != 0)
	{
		if (eval_tree(tree->right) == MEMERR)
			return (MEMERR);
		tree->exit_status = tree->right->exit_status;
	}
	else
		tree->exit_status = tree->left->exit_status;
	return (0);
}

int			eval_tree(t_ast_node *tree)
{
	if (tree == NULL)
		return (-1);
	if ((tree->type == SEMI_COL) || (tree->type == AMPERS)
		|| (tree->type == NEWLINE))
		return (eval_sep(tree));
	else if (tree->type == AND_IF)
		return (eval_and_if(tree));
	else if (tree->type == OR_IF)
		return (eval_or_if(tree));
	else if (tree->type == PIPE)
	{
		if (exec_pipeline(tree) == MEMERR)
			return (MEMERR);
		return (0);
	}
	ft_dprintf(STDERR_FILENO, "21sh: fatal error in eval: unknown node type\n");
	return (-1);
}
