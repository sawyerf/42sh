/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <ktlili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:10:15 by ktlili            #+#    #+#             */
/*   Updated: 2019/06/27 16:20:47 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "readline.h"

char	*quote_err(int errnum)
{
	static char *dq = " seeking enclosing '\"'";
	static char *sq = " seeking enclosing \"'\"";
	static char *e = "";

	if (errnum == DQUOTE_ERR)
		return (dq);
	else if (errnum == SQUOTE_ERR)
		return (sq);
	return (e);
}

int		dispatch_errors(int errnum, t_parser parser)
{
	if (errnum == MEMERR)
	{
		ft_printf("MEMERR exiting..\n");
		exit(1);
	}
	if (errnum == SYNERR || errnum != HEREDOC_ERR)
		g_sh.status = 258;
	if ((errnum == SYNERR) && (parser.current->type != EOI))
		ft_dprintf(STDERR_FILENO, "42sh: syntax error near : '%s'\n",
			parser.current->data.str);
	else if (errnum == HEREDOC_ERR)
		ft_dprintf(STDERR_FILENO, "42sh: heredoci fail\n",
			parser.current->data.str);
	else if ((errnum == CTRL_D) || (errnum == SQUOTE_ERR)
		|| (errnum == DQUOTE_ERR))
		ft_dprintf(STDERR_FILENO, "42sh: premature EOF%s\n", quote_err(errnum));
	else if (errnum == BAD_SUB)
		ft_dprintf(STDERR_FILENO, "42sh: bad substitution\n");
	else if (errnum == BANG_NF)
		ft_dprintf(STDERR_FILENO, "42sh: event not found\n");
	return (errnum);
}

int		parser_is_name_c(char c)
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

void	remove_last_node(t_parser *parser)
{
	t_ast_node *tmp;

	tmp = parser->tree;
	parser->tree = parser->tree->left;
	free(tmp);
}
