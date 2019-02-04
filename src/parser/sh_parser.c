/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/01 14:54:53 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

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
		return;
	free_tree(tree->left);
	free_tree(tree->right);
	if (tree->pipeline)
		free_pipeline(tree->pipeline);
	free(tree);
}
int	test_sh_parser(t_token *start)
{
	t_parser parser;
	int		ret;
/*	char types[100][100] = {"WORD","NEWLINE","IO_NUM","FILENAME", "ASSIGN", "PIPE", "SEMI_COL",
				"AMPERS","ANDIF", "ORIF", "LESSAND", "GREATAND", "DGREAT", "LESS",
				"GREAT"};
*/
	ft_bzero(&parser, sizeof(t_parser));
	parser.current = start;
	parser.head = start;
	ret = expect_complete_cmd(&parser);
	if (parser.current->type != NEWLINE)
		ret = 0;
//	ft_printf("ret = %d token %s |type %s\n", ret, parser.current->data.str, types[parser.current->type]);
	if (ret) 
		eval_tree(parser.tree);
	else
		ft_printf("21sh: syntax error near : '%s'\n", parser.current->data.str);
	free_tree(parser.tree);
//	print_tree(parser.tree);
	return (ret);
}
