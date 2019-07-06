/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:31:28 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/06 17:35:01 by apeyret          ###   ########.fr       */
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
	int		save;

	save = g_sh.mode;
	g_sh.mode = NONINTERACTIVE;
	ft_bzero(&lexer, sizeof(t_lexer));
	init_lexer(line, &lexer);
	/* activate non interactive mode ?*/
	if (ft_lexer(&lexer))
	{
		g_sh.mode = save;
		return (NULL);
	}
	g_sh.mode = save;
	return (lexer.head);
}

static void	overwrite_token(t_token *word, t_token *lxd)
{
	t_token *save;
	t_token *iter;

	save = word->next;
	free(word->data.str);
	ft_memcpy(word, lxd, sizeof(t_token));
	iter = word;
	while ((iter->next) && (iter->next->type != EOI))
		iter = iter->next;
	free_token(iter->next);
	iter->next = save;
	free(lxd);
}

int handle_alias(t_token *word)
{
	char 	*result;
	char	**tab;
	t_token *lxd;
	int		ret;

	if (!(tab = ft_tabnew(1025)))
		return (MEMERR);
	ret = 0;
	while ((result = get_alias(word->data.str, tab)))
	{
		if (!(lxd = lex_alias(result)))
		{
			ft_tabdel(&tab);
			return (MEMERR);
		}
		overwrite_token(word, lxd);
		ret++;
	}
	ft_tabdel(&tab);
	return (ret);
}
