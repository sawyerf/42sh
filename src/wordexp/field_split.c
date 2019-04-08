/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 12:46:44 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/05 19:26:45 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wordexp.h"

int		is_ifs(char c, char *ifs)
{
	while (*ifs)
	{
		if (*ifs == c)
			return (1);
		ifs++;
	}
	return (0);
}

int		split_candidate(char *str, char *ifs)
{
	int index;

	index = 0;
	while (str[index])
	{
		if (is_ifs(str[index], ifs))
			return (1);
		index++;
	}
	return (0);
}

void	trim_str(t_str *str_w, char *ifs)
{
	int	index;

	index = 0;
	while (is_ifs(str_w->str[index], ifs))
		index++;
	ft_memmove(str_w->str, str_w->str + index, ft_strlen(str_w->str) - index);
	str_w->len = str_w->len - index;
	str_w->str[str_w->len] = '\0';
}

void	ft_trim_ifs(t_str *str_w, char *ifs)
{
	trim_str(str_w, ifs);
	ft_strrev(str_w->str);
	trim_str(str_w, ifs);
	ft_strrev(str_w->str);
}


void	replace_token(t_token *word, t_token *new_fields)
{
	t_token			*save;
	t_token_type	type;

	save = word->next;
	type = word->type;
	if (word->data.str)
		free(word->data.str);
	ft_memcpy(word, new_fields, sizeof(t_token));
	word->type = type;
	while (word->next)
		word = word->next;
	word->next = save;
	free(new_fields);
}

char	*expand_ifs(char *ifs)
{
	t_token tmp;

	tmp.type = WORD;
	tmp.data.str = ifs;
	tmp.data.len = ft_strlen(ifs);
	tmp.data.size = ft_strlen(ifs);
	if (ft_wordexp(&tmp, FT_TRUE) == MEMERR)
		return (NULL);
	return (tmp.data.str);
}


t_token	*ft_split_word(char *split_at)
{
	char *half;
	t_token *new;

	half = ft_strdup(split_at);
	*split_at = 0;
	if (!(new = new_token(WORD)))
		return (NULL);
	new->data.str = half;
	new->data.len = ft_strlen(half);
	new->data.size = new->data.len;
	return (new);
}

int		ft_is_ifs(char *ifs, char c)
{
	static char *wspace = " \n\t";

	if (!(ft_cisin(ifs, c)))
		return (0);
	if ((ft_cisin(wspace, c)))
		return (IFS_WSPACE);
	return (IFS_REG);	
}

char	*ft_next_field(char *value, char *ifs)
{
	int i;
	char *new_field;

	i = 0;
	while ((value[i]) && (!ft_is_ifs(ifs, value[i])))
		i++;
	if (!(new_field = ft_strndup(value, i)))
		return (NULL);
	while (ft_is_ifs(ifs, value[i]) == IFS_WSPACE)
		i++;
	if (ft_is_ifs(ifs, value[i]) == IFS_REG)
		i++;
	ft_memmove(value, value + i, ft_strlen(value + i));
	value[ft_strlen(value + i)] = 0;
	return (new_field);
}
void	remove_wspace(char *value, char *ifs)
{
	int i;

	i = 0;
	while (ft_is_ifs(ifs, value[i]) == IFS_WSPACE)
		i++;
	ft_memmove(value, value + i, ft_strlen(value + i));
	value[ft_strlen(value + i)] = 0;
}
char	*extract_field(char *value, char *ifs)
{
	int i;
	char *next_field;

	i = 0;
	while (ft_is_ifs(ifs, value[i]) == IFS_WSPACE)
		i++;
	if ((ft_is_ifs(ifs, value[i]) == IFS_REG))
//		&& (value[i + 1]))
	//	&& ((ft_is_ifs(ifs, value[i + 1]))))
	{
		i++;
//		while (ft_is_ifs(ifs, value[i]) == IFS_WSPACE)
//			i++;
		ft_memmove(value, value + i, ft_strlen(value + i));
		value[ft_strlen(value + i)] = 0;
		return (ft_strdup(""));
	}
	ft_memmove(value, value + i, ft_strlen(value + i));
	value[ft_strlen(value + i)] = 0;
	if (!(next_field = ft_next_field(value, ifs)))
		return (NULL);
	return (next_field);
}
/*
char	*extract_field(char *value, char *ifs)
{
	int i;
	char *next_field;

	i = 0;
	while (ft_is_ifs(ifs, value[i]) == IFS_WSPACE)
		i++;
	if ((ft_is_ifs(ifs, value[i]) == IFS_REG))
//		&& (value[i + 1]))
	//	&& ((ft_is_ifs(ifs, value[i + 1]))))
	{
		i++;
//		while (ft_is_ifs(ifs, value[i]) == IFS_WSPACE)
//			i++;
		ft_memmove(value, value + i, ft_strlen(value + i));
		value[ft_strlen(value + i)] = 0;
		return (ft_strdup(""));
	}
	if ((ft_is_ifs(ifs, value[i]) == IFS_REG))
		i++;
	ft_memmove(value, value + i, ft_strlen(value + i));
	value[ft_strlen(value + i)] = 0;
	if (!(next_field = ft_next_field(value, ifs)))
		return (NULL);
	return (next_field);
}
*/
int		join_token(t_token *word, char *new_field, int before)
{
	char *tmp;
	
	if ((!before) && (!(tmp = ft_strjoin(word->data.str, new_field))))
		return (MEMERR);
	if ((before) && (!(tmp = ft_strjoin(new_field, word->data.str))))
		return (MEMERR);
	free(word->data.str);
	word->data.str =  tmp;
	word->data.len = ft_strlen(tmp);
	word->data.size = ft_strlen(tmp);
	return (0);
}

int		handle_ifs(t_token **word, char **cursor, char *value, char *ifs)
{
	t_token *word_2;
	char	*new_field;
	t_token *tmp;

	if (!(word_2 = ft_split_word(*cursor)))
		return (MEMERR);
	word_2->next = (*word)->next;
	(*word)->next = NULL;
/*	if (ft_is_ifs(ifs, *value)) //if first char is ifs we do not join with word_1
	{
		if (!(new_field = extract_field(value, ifs)))
			return (MEMERR);
		if (split_candidate(value, ifs))
		{
			if (!(tmp = new_token(WORD)))
				return (MEMERR);
			tmp->data.str = new_field;
			tmp->data.len = ft_strlen(new_field);
			tmp->data.size = ft_strlen(new_field);
			(*word)->next = tmp;
		}
		else
		{	
			if (join_token(word_2, new_field, 1) == MEMERR)
				return (MEMERR);
			free(new_field);
		}
		remove_wspace(value, ifs);
	}
	else
	{
		if (!(new_field = extract_field(value, ifs)))
			return (MEMERR);
		if (join_token(*word, new_field, 0) == MEMERR)
			return (MEMERR);
		free(new_field);
	}*/
	//
	if ((ft_is_ifs(ifs, *value)) && ((*word)->data.str[0] != 0))
	{
		if (!(new_field = extract_field(value, ifs)))
			return (MEMERR);
		if (!(tmp = new_token(WORD)))
			return (MEMERR);
		tmp->data.str = new_field;
		tmp->data.len = ft_strlen(new_field);
		tmp->data.size = ft_strlen(new_field);
		(*word)->next = tmp;
	}
	else
	{
		if (!(new_field = extract_field(value, ifs)))
			return (MEMERR);
		if (join_token(*word, new_field, 0) == MEMERR)
			return (MEMERR);
		free(new_field);
	}
	t_token *iter;

	iter = (*word);
	if ((*word)->next)
		iter = (*word)->next;	
	if (iter->next)
	{ //to del
		ft_printf("FATAL ERROR in wordexp");exit(1);}
	while (*value)
	{
		if (!split_candidate(value, ifs))
		{
			if (join_token(word_2, value, 1) == MEMERR)
				return (MEMERR);
//			free(new_field);
			break ;
		}
		if (!(new_field = extract_field(value, ifs))
			|| (!(tmp = new_token(WORD))))
			return (MEMERR);
		remove_wspace(value, ifs);
		tmp->data.str = new_field;
		tmp->data.len = ft_strlen(new_field);
		tmp->data.size = ft_strlen(new_field);
		iter->next = tmp;
		iter = tmp;
	}
	if (word_2->data.str[0] == 0)
	{
		iter->next = word_2->next;
		free_token(word_2);
		*cursor = iter->data.str + ft_strlen(iter->data.str);
		*word = iter->next;
	}
	else
	{
		iter->next = word_2;
		*cursor = word_2->data.str;
		*word = word_2;
	}
	return (0);
}

int		handle_field_split(t_token *word)
{
	static char	*default_ifs = " \t\n";
	char		*ifs;

	if (!(ifs = get_env_value("IFS")))
		ifs = default_ifs;
	else
	{
		if (!(ifs = expand_ifs(ifs)))
			return (MEMERR);
		if (*ifs == 0)
		{
			free(ifs);
			ifs = default_ifs;
		}
	}
	if ((*ifs == '\0') || (!split_candidate(word->data.str, ifs))
		|| (word->type != WORD))
		return (0);
//	if (handle_ifs(word, ifs) == MEMERR)
//		return (MEMERR);
	return (0);
}
/*
int		extract_field(t_str *str_w, int *index, t_token **head, char *ifs)
{
	int		end;
	t_token	*new;

	end = *index;
	while (str_w->str[end])
	{
		if (is_ifs(str_w->str[end], ifs))
			break ;
		if (str_w->str[end] == '\'')
			end = next_squote(str_w->str, end) + 1;
		else if (str_w->str[end] == '"')
			end = next_dquote(str_w->str, end) + 1;
		else if (str_w->str[end] == '\\')
			end = next_bslash(str_w->str, end) + 1;
		else
			end++;
	}
	if ((!(new = new_token(0))) || (str_putnstr(str_w->str + *index,
			&(new->data), end - *index) == MEMERR))
		return (MEMERR);
	add_token(head, new);
	*index = end;
	return (0);
}





int		handle_ifs(t_token *word, char *ifs)
{
	int		index;
	t_token	*new_fields;

	ft_trim_ifs(&(word->data), ifs);
	if (!split_candidate(word->data.str, ifs))
		return (0);
	index = 0;
	new_fields = NULL;
	while (word->data.str[index])
	{
		while (is_ifs(word->data.str[index], ifs))
			index++;
		if (extract_field(&(word->data), &index, &new_fields, ifs) == MEMERR)
			return (MEMERR);
	}
	replace_token(word, new_fields);
	return (0);
}

*/
