/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/02 19:57:43 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "readline.h"

int	parser_is_name_c(char c)
{
	if ((c == '_') || (ft_isalnum(c)))
		return (1);
	return (0);
}

int		parser_is_assign(t_token const *token)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	ptr = token->data.str;
	while ((ptr[i]) && (ptr[i] != '='))
		i++;
	if (ptr[i] != '=')
		return (0);
	if (ft_isdigit(ptr[0]))
		return (0);
	j = 1;
	while (j < i)
	{
		if (!parser_is_name_c(ptr[j]))
			return (0);
		j++;
	}
	return (1);
}

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

t_ast_node	*get_tree(t_ast_node *tree)
{
	static t_ast_node *static_tree = NULL;

	if (tree)
		static_tree = tree;
	return (static_tree);
}

void	remove_last_node(t_parser *parser)
{
	t_ast_node *tmp;

	tmp = parser->tree;
	parser->tree = parser->tree->left;
	free(tmp);
}

int	next_token(t_parser *parser)
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

int	execute_cmdline(t_parser *parser)
{
	if (eval_tree(parser->tree) == MEMERR)
		return (MEMERR);
	free_tree(parser->tree);
	parser->tree = NULL;
	ft_bzero(&(parser->cmd), sizeof(t_simple_cmd));
	return (0);
}

int	dispatch_errors(int errnum, t_parser parser)
{
	if (errnum == MEMERR)
	{
		ft_printf("MEMERR exiting..\n");
		exit(1);
	}
	if (errnum == SYNERR || errnum != HEREDOC_ERR)
		g_sh.status = 258;
	if ((errnum == SYNERR) && (parser.current->type != EOI))
		ft_dprintf(STDERR_FILENO, "21sh: syntax error near : '%s'\n",
			parser.current->data.str);
	else if (errnum == HEREDOC_ERR)
		ft_dprintf(STDERR_FILENO, "21sh: premature EOF on heredoc\n",
			parser.current->data.str);
	else if (errnum == CTRL_D)
		ft_dprintf(STDERR_FILENO, "21sh: premature EOF\n");
	return (errnum);
}

int	sh_parser_refac(char *line)
{
	t_parser	parser;
	t_lexer		lexer;
	int			ret;

	ft_bzero(&parser, sizeof(t_parser));
	ft_bzero(&lexer, sizeof(t_lexer));
	init_lexer(line, &lexer);
	parser.lx_state = &lexer;
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
