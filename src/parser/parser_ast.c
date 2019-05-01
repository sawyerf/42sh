/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 14:30:55 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/09 21:12:24 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

int		tree_add_sep(t_parser *parser)
{
	t_ast_node *node;

	if (!(node = ft_memalloc(sizeof(t_ast_node))))
		return (MEMERR);
	node->type = parser->current->type;
	add_to_tree(&(parser->tree), node);
	return (0);
}

int		tree_add_nl(t_parser *parser)
{
	t_ast_node *node;

	if (!(node = ft_memalloc(sizeof(t_ast_node))))
		return (MEMERR);
	node->type = NEWLINE;
	add_to_tree(&(parser->tree), node);
	return (0);
}

int		tree_add_and_or(t_parser *parser)
{
	t_ast_node *node;

	if (!(node = ft_memalloc(sizeof(t_ast_node))))
		return (MEMERR);
	node->type = parser->current->type;
	add_to_tree(&(parser->tree), node);
	return (0);
}

int		tree_add_pipeline(t_parser *parser)
{
	t_ast_node *node;

	if (!(node = ft_memalloc(sizeof(t_ast_node))))
		return (MEMERR);
	node->pipeline = parser->pipeline;
	node->type = PIPE;
	add_to_tree(&(parser->tree), node);
	parser->pipeline = NULL;
	return (0);
}

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
		if (insert == *head)
			replace_higher(head, to_add);
		else
			replace_right(insert, to_add);
	}
	else if ((to_add->type == OR_IF) || (to_add->type == AND_IF))
	{
		while ((insert->right) && (is_sep(insert->right)))
			insert = insert->right;
		if ((insert == *head) && ((insert->type == OR_IF)
			|| (insert->type == AND_IF)))
			replace_higher(head, to_add);
		else
			replace_right(insert, to_add);
	}
}
