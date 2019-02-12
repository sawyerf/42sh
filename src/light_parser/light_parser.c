/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:58:34 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/12 15:47:20 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_light_parser.h"

int fill_autocomp(t_autocomplete *autocomp, t_expecting type, char *str)
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
/*
int do_stuff(t_token *start, t_autocomplete *autocomp)
{
	t_expecting expecting;
	int			first_word;

	expecting = cmd_name;
	first_word = 1;
	while (start->type != NEWLINE)
	{
		if (start->type == WORD)
			first_word = 0;
		else if ((start->type >= LESSAND) && (start->type <= GREAT))

		start = start->next;
		
	}
}
*/
int	is_first_word(char *line, t_token *start, t_autocomplete *autocomp)
{
	int first_word;
	t_token *save;

	first_word = 1;
	save = start;
	start = start->next;
	while (start->type != NEWLINE)
	{
		if (start->type == WORD)
		{
			first_word = 0;
			break;	
		}
		start = start->next;
	}
	if (save->type == WORD)
	{
		if  (!ft_is_whitespace(*line) && (first_word))
			return (fill_autocomp(autocomp, cmd_name, save->data.str));
		else if ((!ft_is_whitespace(*line)) && (!first_word))
			return (fill_autocomp(autocomp, arg, save->data.str));
	}
	return (fill_autocomp(autocomp, arg, ""));
	return (0);
}

int dispatch_types(char *line, t_token *start, t_autocomplete *autocomp)
{

	if ((start->type >= PIPE) && (start->type <= GREAT))
	{
		if ((start->type >= LESSAND) && (start->type <= GREAT))
			return (fill_autocomp(autocomp, arg, ""));
		return (fill_autocomp(autocomp, cmd_name, ""));
	}
	return (is_first_word(line, start, autocomp));
}

int	ft_light_parser(char *line, t_autocomplete *autocomplete)
{
	t_token *tokens;

	
	ft_strrev(line);
	if (*line == '\n')
		ft_memmove(line, line + 1, ft_strlen(line));
	if (rev_lex(line, &tokens) == MEMERR)
		return (MEMERR);
	if (dispatch_types(line, tokens, autocomplete) == MEMERR)
		return (MEMERR);
	return (0);
}
