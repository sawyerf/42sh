/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:43 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/05 18:18:47 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

static	size_t	quote_str_len(char *str)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '\'') || (str[i] == '"') || (str[i] == '\\'))
			count++;
		i++;
	}
	return (count);
}

char	*quote_str(char *str)
{
	size_t	count;
	int		j;
	int		i;
	char	*quoted;

	count = quote_str_len(str);
	i = ft_strlen(str);
	if (!(quoted = ft_strnew(i + count)))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'') || (str[i] == '"') || (str[i] == '\\'))
		{
			quoted[j] = '\\';
			j++;
		}
		quoted[j] = str[i];
		i++;
		j++;
	}
	return (quoted);
}

/*
int		expand_param(t_str *str_w, int *index, char *to_insert)
{
	int		trunc;
	int		i;

	i = *index + 1;
	trunc = 1;
	if (str_w->str[i] == '{')
	{
		i++;
		trunc = 3;
	}
	while (parser_is_name_c(str_w->str[i]))
	{
		trunc++;
		i++;
	}
	ft_memmove(str_w->str + *index, str_w->str + *index + trunc,
			str_w->len - *index - trunc);
	str_w->len = str_w->len - trunc;
	str_w->str[str_w->len] = '\0';
	if (insert_str(str_w, index, to_insert) == MEMERR)
		return (MEMERR);
	return (0);
}
*/
char	*build_param(char *cursor)
{
	static char	*empty_str = "";
	char		*value;

	if (*cursor == '{')
		cursor++;
	value = get_env_value(cursor + 1);
	if (!value)
		value = empty_str;
	if (!(value = quote_str(value)))
		return (NULL);
	return (value);
}
/*
char	*build_param(t_str *str_w, int index)
{
	static char	*empty_str = "";
	char		*value;

	if (str_w->str[index] == '{')
		index++;
	value = get_env_value(str_w->str + index);
	if (!value)
		value = empty_str;
	if (!(value = quote_str(value)))
		return (NULL);
	return (value);
}*/
/*
t_token *expand_param(t_token word, int *index, char *value)
{

}
 expand_param checks for flag for redir, if not redir split to_insert by ifs and insert original token at *index. strjoin the first half of word with the first str in the char ** resulting from to_insert split IF s[0] not in ifs. while char[i++] != NULL, generate new token, link to prev word, when char[i] == NULL strjoin whatever is left in initial string if s[len(s)] != ifs


	s = s + *index
	tk = ft_duptoken(word);
	head = tk;
	if is_ifs(s[0])
		s[0] = 0;
		tk = create_token()
		add_tk(&head, tk)
	trim_wspace(IFS[whitespace], s)
	while (*s)
		if (*s in IFS)
			if (not in whitespace)
			{
				// add \0 somewhere around here
				add_tk(head, tk)
				tk = create_token()
			}
			consume_ifs(ifs, &s)
		else
			str_putc(&s, tk->data.str)
		
*/
/*
0- delete varname from token
1- if not split candidate, proceed as before
2- if split candidate:
	0) split word in 2 words: word1 and word2, word2->next=word1->n word1->next=word2
	*index should point to word2->str[0]
	1) extract first field
	2) if (first char in ifs)
		generate new token with new field
		new_field->next = word1->next;
		word1->next = new_field;	         //aka add_token
		last = new_field
	2) else
		replace(strjoin(word1->str, new_field))
		last = word1

	while (ifs)
		to_insert++;
	4) iterate over to_insert
	{
			if (!split_candidate)
				replace(strjoin(word2->str, new_field))
			1) extract next_field from to_insert and delete IFS after field
				generate new token with new field
				new_field->next = last->next;
				last->next = new_field;	         //aka add_token
	}
		
		
	1) extract first field from value to value == 0 or value == IFS

*/

int		get_ifs(char **ifs)
{
	static char *default_ifs = "  \t\n";

	if (!(*ifs = get_env_value("IFS")))
		*ifs = default_ifs;
	else
	{
		if (!(*ifs = expand_ifs(*ifs)))
			return (MEMERR);
		if (*ifs == 0)
		{
			free(*ifs);
			*ifs = NULL;
		}
	}
	return (0);
}

void		delete_varname(char *cursor)
{
	int		trunc;
	int		i;

	i = 1;
	trunc = 1;
	if (*(cursor + 1) == '{')
	{
		i++;
		trunc = 3;
	}
	while (parser_is_name_c(cursor[i]))
	{
		trunc++;
		i++;
	}
	i = ft_strlen(cursor + trunc);
	ft_memmove(cursor, cursor + trunc, ft_strlen(cursor + trunc));
	cursor[i] = 0;
//	ft_memmove(str_w->str + *index, str_w->str + *index + trunc,
//			str_w->len - *index - trunc);
//	str_w->len = str_w->len - trunc;
//	str_w->str[str_w->len] = '\0';
	return ;
}


int		expand_param(t_token **word, char **cursor, char *value, t_bool is_redir)
{
	char				*ifs;
	int					i;

	if (get_ifs(&ifs) == MEMERR)
		return (MEMERR);
	delete_varname(*cursor);
	if ((!ifs) || (is_redir == FT_TRUE) || (!split_candidate(value, ifs)))
	{
	//	tmp = *cursor;
//	*cursor = *cursor + ft_strlen(value);
		i = *cursor - (*word)->data.str;
		if (c_insert_str(*word, *cursor, value) == MEMERR)
			return (MEMERR);
		*cursor = (*word)->data.str + i + strlen(value);
		return (0);
	}
	return(handle_ifs(word, cursor, value, ifs));
}

int		handle_exp_param(t_token *word, t_bool is_redir)
{
	char	*cursor;
	char	*value;
	int		inside_dquote;

	cursor = word->data.str;
	inside_dquote = 1;
	while (*cursor)
	{
		if (*cursor == '"')
			inside_dquote = -inside_dquote;
		if ((*cursor == '$') && (*(cursor + 1) != 0))
		{
			if ((!(value = build_param(cursor))
			|| (expand_param(&word, &cursor, value, is_redir) == MEMERR)))
				return (MEMERR);
			free(value);
			continue;
		}
		else if ((*cursor == '\'') && (inside_dquote == 1))
			cursor = c_next_squote(cursor);
		else if (*cursor == '\\')
			cursor = c_next_bslash(cursor);
		cursor++;
	}
	return (0);
}

/*
int		handle_exp_param(t_token *word, t_bool is_redir)
{
	int		index;
	char	*value;
	int		inside_dquote;

	index = 0;
	inside_dquote = 1;
	while (word->data.str[index])
	{
		if (word->data.str[index] == '"')
			inside_dquote = -inside_dquote;
		if ((word->data.str[index] == '$') && (word->data.str[index + 1] != 0))
		{
			if ((!(value = build_param(&(word->data), index + 1)))
			|| (expand_param(&(word->data), &index, value) == MEMERR))
				return (MEMERR);
			free(value);
			continue;
		}
		else if ((word->data.str[index] == '\'') && (inside_dquote == 1))
			index = next_squote(word->data.str, index);
		else if (word->data.str[index] == '\\')
			index = next_bslash(word->data.str, index);
		index++;
	}
	return (0);
}*/
