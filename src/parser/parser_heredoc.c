/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:33:08 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/01 15:39:52 by apeyret          ###   ########.fr       */
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

static int	interactive_heredoc(t_token *io_here)
{
	size_t		len;
	char		*here_doc;
	char		*new_ln;
	char		*tmp;
	t_read_fn	read_fn;

	read_fn = readline;
	if (g_sh.mode != INTERACTIVE)
		read_fn = sh_readfile;
	len = ft_strlen(io_here->data.str);
	if (!(here_doc = ft_strdup("")))
		return (MEMERR);
	while (42)
	{
		if ((read_fn("heredoc> ", &new_ln))
			|| (new_ln == '\0'))
			// this is wrong */
		{
			free(here_doc);
			return (HEREDOC_ERR);
		}
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

char		*get_file_delim(char *next_nl, char *here_end, t_parser *parser)
{
	char	*delim;
	char	*ln;
	int		len;
	char	*tmp;

	(void)parser;
	len = ft_strlen(here_end);
	while (42)
	{
		readline(">", &ln);
		if ((!ln) || (*ln == 0))
			return (NULL);
		free(next_nl);
		tmp = ft_strjoin(next_nl, ln);
		free(next_nl);
		next_nl = tmp;
		delim = ft_strstr(next_nl, here_end);
		if ((delim[len] == '\n') || (delim[len] == '\0'))
			return (delim);
		next_nl = delim + len;
	}
	return (NULL);
}

int			handle_here_doc(t_parser *parser)
{
	char	*next_nl;
	char	*here_end;
	char	*delim;
	char	*here_doc;
	int		len;
	int		tocpy;

	if (here_doc_delimiter(parser->current) == MEMERR)
		return (MEMERR);
	//if (g_sh.mode == INTERACTIVE)
	return (interactive_heredoc(parser->current));
	if (!(here_end = ft_zprintf("\n%s", parser->current->data.str)))
		return (MEMERR);
	next_nl = parser->cursor;
	if (!(delim = get_file_delim(next_nl, here_end, parser)))
		return (HEREDOC_ERR);
	if (!(here_doc = ft_strndup(next_nl, delim - next_nl + 1)))
		return (MEMERR);
	len = delim - next_nl + ft_strlen(here_end) + 1;
	tocpy = ft_strlen(delim + ft_strlen(here_end));
	ft_memmove(next_nl, next_nl + len, tocpy);
	next_nl[tocpy] = 0;
	free(here_end);
	replace_here_doc(parser->current, here_doc);
	return (0);
}
