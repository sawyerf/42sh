/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:58:34 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/18 18:44:40 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_light_parser.h"

static int fill_autocomp(t_autocomplete *autocomp, t_expecting type, char *str)
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
	int first_word;
	t_token *save;

	first_word = 1;
	save = start;
	start = start->next;
	while (start && start->type != NEWLINE)
	{
		if ((start->type == WORD) && (!parser_is_assign(start)))
		{
			first_word = 0;
			break;	
		}
		start = start->next;
	}
	if (save->type == WORD)
	{
		if  (!ft_is_whitespace(*line) &&  first_word)
			return (fill_autocomp(autocomp, cmd_name, save->data.str));
		else if ((!ft_is_whitespace(*line)) && (!first_word))
			return (fill_autocomp(autocomp, arg, save->data.str));
	}
	return (fill_autocomp(autocomp, arg, ""));
}

static int dispatch_types(char *line, t_token *start, t_autocomplete *autocomp)
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
/*
 */
int	ft_light_parser(char *lin, t_autocomplete *autocomplete)
{
	t_token *tokens;
	char 	*line;

	if (!(line = ft_strdup(lin)))
		return (MEMERR);
	ft_strrev(line);
	if (*line == '\n')
		ft_memmove(line, line + 1, ft_strlen(line));
	if (rev_lex(line, &tokens) == MEMERR 
			|| dispatch_types(line, tokens, autocomplete) == MEMERR)
	{
		ft_strdel(&line);
		return (MEMERR);
	}
	ft_strdel(&line);
	return (0);
}
