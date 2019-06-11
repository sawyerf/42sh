/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/14 19:02:38 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "readline.h"

static void	init_parser(t_parser *parser, t_lexer *lexer, char *line)
{
	ft_bzero(parser, sizeof(t_parser));
	ft_bzero(lexer, sizeof(t_lexer));
	init_lexer(line, lexer);
	parser->lx_state = lexer;
}

int			next_token(t_parser *parser)
{
	int ret;

	if ((parser->current) && (parser->current->next))
	{
		parser->current = parser->current->next;
		return (0);
	}
	ret = ft_lexer(parser->lx_state);
	if ((parser->current))
		parser->current->next = parser->lx_state->head;
	parser->current = parser->lx_state->head;
	if ((parser->lx_state->err) || (ret))
		return (parser->lx_state->err);
	parser->cursor = parser->lx_state->cursor;
	return (0);
}

int			execute_cmdline(t_parser *parser)
{
	if (eval_tree(parser->tree) == MEMERR)
		return (MEMERR);
	free_tree(parser->tree);
	parser->tree = NULL;
	ft_bzero(&(parser->cmd), sizeof(t_simple_cmd));
	return (0);
}

void		add_to_tree(t_ast_node **head, t_ast_node *to_add)
{
	if (*head == NULL)
	{
		*head = to_add;
		return ;
	}
	if (to_add->type == PIPE)
	{
		if ((*head)->right == NULL)
			(*head)->right = to_add;
		else
			(*head)->right->right = to_add;
	}
	return (add_to_tree_sep(head, to_add));
}

int			sh_parser(char *line)
{
	t_parser	parser;
	t_lexer		lexer;
	int			ret;

	init_parser(&parser, &lexer, line);
	if ((ret = next_token(&parser)))
	{
		dispatch_errors(ret, parser);
		free(parser.lx_state->line);
		free_token_lst(parser.lx_state->head);
		return (parser.lx_state->err);
	}
	parser.head = parser.lx_state->head;
	ret = expect_complete_cmds(&parser);
	free(parser.lx_state->line);
	if (ret)
	{
		dispatch_errors(ret, parser);
		free_token_lst(parser.head);
		free_tree(parser.tree);
		return (ret);
	}
	free_token_lst(parser.head);
	return (0);
}
