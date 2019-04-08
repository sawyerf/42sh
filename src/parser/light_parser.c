/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:58:34 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/08 19:40:02 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_light_parser.h"

static int	fill_autocomp(t_autocomplete *autocomp, t_expecting type, char *str)
{
	int i;

	i = 0;
	autocomp->type = type;
	while (parser_is_name_c(str[i]))
		i++;
	if ((str[i] == '$') || (!ft_strcmp(str + i, "{$")))
		autocomp->type = param;
	ft_strrev(str);
	if (!(autocomp->str = ft_strdup(str)))
		return (MEMERR);
	return (0);
}

static int	is_first_word(char *line, t_token *start, t_autocomplete *autocomp)
{
	int		first_word;
	t_token	*save;

	first_word = 1;
	save = start;
	start = start->next;
	while (start && start->type != NEWLINE)
	{
		if (((start->type == WORD) && (!parser_is_assign(start)))
				|| ((start->type >= LESSAND) && (start->type <= GREAT)))
		{
			first_word = 0;
			break ;
		}
		start = start->next;
	}
	if (save->type == WORD)
	{
		if (!ft_is_whitespace(*line) && first_word)
			return (fill_autocomp(autocomp, cmd_name, save->data.str));
		else if ((!ft_is_whitespace(*line)) && (!first_word))
			return (fill_autocomp(autocomp, arg, save->data.str));
	}
	return (fill_autocomp(autocomp, arg, ""));
}

static int	dispatch_types(char *line, t_token *start, t_autocomplete *autocomp)
{
	if (((start->type >= PIPE) && (start->type <= GREAT))
			|| (start->type == NEWLINE))
	{
		if ((start->type >= LESSAND) && (start->type <= GREAT))
			return (fill_autocomp(autocomp, arg, ""));
		return (fill_autocomp(autocomp, cmd_name, ""));
	}
	return (is_first_word(line, start, autocomp));
}

int			exp_tilde(t_autocomplete *acp)
{
	t_str	tmp;
	int		dummy;

	if (!(acp->str[0] == '~') || !(tilde_valid(acp->str[1])))
		return (0);
	ft_bzero(&tmp, sizeof(t_str));
	dummy = 0;
	tmp.str = acp->str;
	tmp.size = ft_strlen(acp->str);
	tmp.len = tmp.size;
	if (expand_tilde(&tmp, &dummy, 0) == MEMERR)
		return (MEMERR);
	acp->str = tmp.str;
	return (0);
}

void		clear_autocom(t_autocomplete *autoc)
{
	int i;

	i = 0;
	ft_strrev(autoc->str);
	while (autoc->str[i])
	{
		if ((autoc->str[i] == '"') || (autoc->str[i] == '\'')
			|| (autoc->str[i] == '\\'))
		{
			if (autoc->str[i + 1])
				autoc->type = arg;
			autoc->str[i] = 0;
			ft_strrev(autoc->str);
			return ;
		}
		i++;
	}
	ft_strrev(autoc->str);
	return ;
}

int			ft_light_parser(char *lin, t_autocomplete *autocomplete)
{
	t_token	*tokens;
	char	*line;
	int		mode;

	mode = g_sh.mode;
	g_sh.mode = NONINTERACTIVE;
	if (!(line = ft_strdup(lin)))
		return (MEMERR);
	ft_strrev(line);
	if (*line == '\n')
		ft_memmove(line, line + 1, ft_strlen(line));
	if (rev_lex(line, &tokens) == MEMERR
			|| dispatch_types(line, tokens, autocomplete) == MEMERR
				|| (exp_tilde(autocomplete) == MEMERR))
	{
		ft_strdel(&line);
		return (MEMERR);
	}
	clear_autocom(autocomplete);
	g_sh.mode = mode;
	free_token_lst(tokens);
	ft_strdel(&line);
	return (0);
}
