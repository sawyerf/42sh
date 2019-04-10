/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 14:30:55 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/10 20:05:04 by ktlili           ###   ########.fr       */
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

void	add_to_tree_sep(t_ast_node **head, t_ast_node *to_add)
{
	if ((to_add->type == SEMI_COL) || (to_add->type == NEWLINE))
	{
		to_add->left = *head;
		*head = to_add;
	}
	else if ((to_add->type == OR_IF) || (to_add->type == AND_IF))
	{
		if ((*head)->type == SEMI_COL)
		{
			to_add->left = (*head)->right;
			(*head)->right = to_add;
		}
		else
		{
			to_add->left = *head;
			*head = to_add;
		}
	}
}
