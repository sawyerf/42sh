/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/08 15:47:51 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_light_parser.h"

static int		is_param(char const*token)
{
	int i;

	if (token[0] != '$')
		return (0);
	i = 1;
	while (token[i])
	{
		if (!valid_env_char(token[i]))
				return (0);
		i++;
	}
	return (1);
}
/*
 *	- ft_light_parser takes commandline fills t_autocomplete struct with string of 
 *	last valid token for auto completion + it's type (cmd_name or arg or param).
 *	- *line should never be NULL.
 *	- Empty *line will return cmd_name.
 *	- Ignores invalid syntax cmdline
 *	
 */
int		ft_light_parser(char *line, t_autocomplete *autocomplete)
{
	t_token 	*tokens;
	t_token 	*iter;
	t_token		*save;
	int			first_word;
	t_expecting expecting;

	tokens = NULL;
	if (!*line)
		return (1);
	ft_strrev(line); /* invert line since we are interested in last tokens only*/
	expecting = cmd_name;
	if (ft_tokenizer_2(line, &tokens) == MEMERR)
		return (MEMERR);
	if  ((tokens->type >= PIPE) && (tokens->type <= GREAT))
/* last token is an operator, expecting cmd_name*/
	{
		autocomplete->type = expecting;
		if  ((tokens->type >= LESSAND) && (tokens->type <= GREAT))
			autocomplete->type = arg;
		autocomplete->str = ft_strdup ("");
		if (autocomplete->str == NULL)
			return (MEMERR);
		return (0);
	}
	first_word = 1;
	iter = tokens->next;
	save = tokens;
	while (iter->type != NEWLINE)
	{
		if  ((iter->type >= PIPE) && (iter->type <= OR_IF))
			break;
		if (iter->type == WORD)
		{
			first_word = 0;
			break;
		}
		iter = iter->next;
	}
	if ((first_word) && (!ft_is_whitespace(*line))) 
		expecting = cmd_name; /* last token is first 
								 	word in cmdline and is not delimited by spaces*/
	else
		expecting = arg;
	autocomplete->type = expecting;
	/*  (*line) points to last char since we inverted it
	 *  if last token has been delimited we return empty str
	 *  else we return whatever is in the token
	 */ 
	if ((save->type == WORD) && (!ft_is_whitespace(*line)))
		autocomplete->str = ft_strdup(save->data.str);
	else 
		autocomplete->str = ft_strdup("");
	if (autocomplete->str == NULL)
		return (MEMERR);
	ft_strrev(autocomplete->str);
	if (is_param(autocomplete->str)) /* param is beginning of shell expansion with $*/ 
		autocomplete->type = param;
	free_token_lst(tokens);
	return (0);
}
