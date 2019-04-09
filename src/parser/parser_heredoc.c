/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:33:08 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/09 21:12:56 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "readline.h"

static int	here_doc_delimiter(t_token *io_here)
{
	size_t	len;

	len = ft_strlen(io_here->data.str);
	if (quote_removal(io_here) == MEMERR)
		return (MEMERR);
	io_here->type = HERE_END;
	if (len > ft_strlen(io_here->data.str))
		io_here->type = HERE_END_QU;
	return (0);
}

static void	replace_here_doc(t_token *io_here, char *here_doc)
{
	free(io_here->data.str);
	io_here->data.str = here_doc;
	io_here->data.len = ft_strlen(here_doc);
	io_here->data.size = ft_strlen(here_doc) + 1;
}

static int	here_doc_err(char *to_free, int ret)
{
	free(to_free);
	if (ret == MEMERR)
		return (MEMERR);
	return (HEREDOC_ERR);
}

int			read_heredoc(t_token *io_here, size_t len)
{
	char		*here_doc;
	char		*new_ln;
	char		*tmp;
	t_read_fn	read_fn;
	int			ret;

	read_fn = (g_sh.mode == INTERACTIVE) ? readline : sh_readfile;
	if (!(here_doc = ft_strdup("")))
		return (MEMERR);
	while (42)
	{
		if ((ret = read_fn("heredoc> ", &new_ln)))
			return (here_doc_err(here_doc, ret));
		if ((!ft_strncmp(new_ln, io_here->data.str, len))
			&& (new_ln[len] == '\n'))
			break ;
		if (!(tmp = ft_strjoin(here_doc, new_ln)))
			return (MEMERR);
		free(new_ln);
		free(here_doc);
		here_doc = tmp;
	}
	free(new_ln);
	replace_here_doc(io_here, here_doc);
	return (0);
}

int			handle_here_doc(t_parser *parser)
{
	size_t len;

	if (here_doc_delimiter(parser->current) == MEMERR)
		return (MEMERR);
	len = ft_strlen(parser->current->data.str);
	return (read_heredoc(parser->current, len));
}
