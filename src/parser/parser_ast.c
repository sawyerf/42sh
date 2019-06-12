/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 14:30:55 by ktlili            #+#    #+#             */
/*   Updated: 2019/05/04 20:13:05 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

char		*make_cmdline(t_token *start, t_token *end, int last)
{
	char	*ln;
	size_t	tot_len;
	t_token *iter;

	tot_len = 0;
	iter = start;
	while (iter)
	{
		tot_len += ft_strlen(iter->data.str) + 1; // + 1 for whitespace
		if (iter == end)
			break;
		iter = iter->next;
	}
	if (!(ln = ft_strnew(tot_len)))
		return (NULL);
	iter = start;
	while (iter)
	{
		ft_strcat(ln, iter->data.str);
		if (iter == end)
			break;
		iter = iter->next;
		if ((!last) && (iter == end))
			break;
		ft_strcat(ln, " ");
	}
	return (ln);
}

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
