/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/12 23:14:47 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_lexer.h"

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
/*
t_token	next_sym(t_token *parser)
{

	t_token *tmp;
	
	tmp = parser;
	while (tmp->next)
		tmp = tmp->next;
	next_token(NULL, &tmp);
	return (tmp->next);
}

int	sh_parser(char *line)
{
	t_parser	parser;
	t_token		*current;
	char		*iter;
	int			ret;

	iter = line;
	next_token(line, &(parser.head));
	parser.current = parser.head;
	ret = expect_complete_cmd(&parser);
	ft_printf("ret = %d token %s type %d\n", ret, parser.current->data.str, parser.current->type);
}
*/
int	test_sh_parser(t_token *start)
{
	t_parser parser;
	int		ret;
	char types[100][100] = {"WORD","NEWLINE","IO_NUM","FILENAME", "ASSIGN", "PIPE", "SEMI_COL",
				"AMPERS","ANDIF", "ORIF", "LESSAND", "GREATAND", "DGREAT", "LESS",
				"GREAT"};

	ft_bzero(&parser, sizeof(t_parser));
	parser.current = start;
	parser.head = start;
	ret = expect_complete_cmd(&parser);
	if (parser.current->type != NEWLINE)
		ret = 0;
	ft_printf("ret = %d token %s |type %s\n", ret, parser.current->data.str, types[parser.current->type]);
	t_simple_cmd *tmp;

	tmp = parser.pipeline;
	return (ret);
}
