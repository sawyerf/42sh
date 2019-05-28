/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:31:28 by ktlili            #+#    #+#             */
/*   Updated: 2019/05/28 17:48:35 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"


static t_token *lex_alias(char *line)
{
	t_lexer lexer;

	ft_bzero(&lexer, sizeof(t_lexer));
	init_lexer(line, &lexer);
	/* activate non interactive mode ?*/
	if (ft_lexer(&lexer))
		return (lexer.err);
	return (lexer.head);
}

static void	overwrite_token(t_token *word, t_token *lxd)
{
	t_token *save;
	t_token *iter;

	save = word->next;
	ft_memcpy(word, lxd, sizeof(t_token));
	iter = lxd;
	while (iter->next)
		iter = iter->next;
	iter->next = save;
}

int handle_alias(t_token *word)
{
	char *dummy = "toto";
	char *result = "ls - l ; echo hello > file"
	t_token *lxd;

	if (!ft_strequ(dummy, word->data.str))
	{
		if (!(lxd = lex_alias(result)))
			return (MEMERR);
		overwrite_token(word, lxd)
		return (0);
	}
	return (0);
}
