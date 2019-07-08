/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 14:30:55 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/08 19:55:31 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

int		tree_add_sep(t_parser *parser)
{
	t_ast_node *node;

	if (!(node = ft_memalloc(sizeof(t_ast_node))))
		return (MEMERR);
	node->type = parser->current->type;
	node->start = parser->start;
	node->end = parser->end;
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

int		tree_add_pipeline(t_parser *parser, t_token *start)
{
	t_ast_node *node;

	if (!(node = ft_memalloc(sizeof(t_ast_node))))
		return (MEMERR);
	node->start = start;
	node->end = parser->current;
	node->pipeline = parser->pipeline;
	node->type = PIPE;
	add_to_tree(&(parser->tree), node);
	parser->pipeline = NULL;
	return (0);
}
