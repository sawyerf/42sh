/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:31:28 by ktlili            #+#    #+#             */
/*   Updated: 2019/05/28 17:54:36 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

extern t_sh g_sh;

char	*get_alias(char *s, char **tab)
{
	while (*tab)
	{
		if (!ft_strcmp(*tab, s))
			return (NULL);
		tab++;
	}
	if (varchr(g_sh.alias, s))
	{
		if (!(*tab = ft_strdup(s)))
			return (NULL);
		return (varchr(g_sh.alias, s));
	}
	return (NULL);
}

static t_token *lex_alias(char *line)
{
	t_lexer lexer;

	ft_bzero(&lexer, sizeof(t_lexer));
	init_lexer(line, &lexer);
	/* activate non interactive mode ?*/
	if (ft_lexer(&lexer))
		return (NULL);
	return (lexer.head);
}

static void	overwrite_token(t_token *word, t_token *lxd)
{
	t_token *save;
	t_token *iter;

	save = word->next;
	ft_memcpy(word, lxd, sizeof(t_token));
	iter = lxd;
	while ((iter->next) && (iter->next->type != EOI))
		iter = iter->next;
	iter->next = save;
}

int handle_alias(t_token *word)
{
	char 	*result;
	char	**tab;
	t_token *lxd;

	if (!(tab = ft_tabnew(1025)))
		return (MEMERR);
	while ((result = get_alias(word->data.str, tab)))
	{
		if (!(lxd = lex_alias(result)))
		{
			ft_tabdel(&tab);
			return (MEMERR);
		}
		overwrite_token(word, lxd);
		return (1);
	}
	ft_tabdel(&tab);
	return (0);
}
