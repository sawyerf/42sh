/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast_sep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 19:52:34 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 19:53:04 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

void	replace_right(t_ast_node *parent, t_ast_node *new)
{
	new->left = parent->right;
	parent->right = new;
}

void	replace_left(t_ast_node *parent, t_ast_node *new)
{
	new->left = parent->left;
	parent->left = new;
}

void	replace_higher(t_ast_node **node, t_ast_node *new)
{
	new->left = *node;
	*node = new;
}

int		is_sep(t_ast_node *n)
{
	if ((n->type == SEMI_COL) || (n->type == AMPERS)
			|| (n->type == NEWLINE))
		return (1);
	return (0);
}

void	add_to_tree_sep(t_ast_node **head, t_ast_node *to_add)
{
	t_ast_node *insert;

	insert = *head;
	if ((to_add->type == SEMI_COL) || (to_add->type == AMPERS)
			|| (to_add->type == NEWLINE))
	{
		while ((insert->right) && (is_sep(insert->right)))
			insert = insert->right;
		if (!is_sep(insert))
			replace_higher(head, to_add);
		else
			replace_right(insert, to_add);
	}
	else if ((to_add->type == OR_IF) || (to_add->type == AND_IF))
	{
		while ((insert->right) && (is_sep(insert->right)))
			insert = insert->right;
		if (is_sep(insert))
			replace_right(insert, to_add);
		else
			replace_higher(head, to_add);
	}
}
