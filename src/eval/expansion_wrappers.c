/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wrappers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 11:48:18 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/04 22:31:28 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

void		token_to_array(t_token *word, char **array)
{
	int i;

	i = 0;
	while (word)
	{
		array[i] = word->data.str;
		word->data.str = NULL;
		word = word->next;
		i++;
	}
	return ;
}

void	remove_token(t_simple_cmd *cmd, t_token *todel)
{
	t_token *tmp;

	tmp = todel->next;
	if (todel == cmd->word_lst)
	{
		free_token(todel);
		cmd->word_lst = tmp;
		return ;
	}
	tmp = cmd->word_lst;
	while (tmp->next)
	{
		if (tmp->next == todel)
		{
			tmp->next = todel->next;
			free_token(todel);
			return ;
		}
		tmp = tmp->next;
	}
}

int			is_quoted(char *str)
{
	while (*str)
	{
		if (ft_cisin("'\"\\", *str))
			return (1);
		str++;
	}
	return (0);
}

int			expand_token_lst(t_simple_cmd *sim_cmd)
{
	t_token	*iter;
	t_token	*save;
	t_token *prev;
	int		quoted;

	iter = sim_cmd->word_lst;
	prev = NULL;
	while (iter)
	{
		quoted = is_quoted(iter->data.str);
		save = iter->next;
		if (ft_wordexp(iter, FT_FALSE) == MEMERR)
			return (MEMERR);
		if ((!quoted) && (iter->data.str[0] == 0))
			remove_token(sim_cmd, iter);
		prev = iter;
		iter = save;
	}
	return (0);
}

char		**tokens_to_str(t_token *word)
{
	size_t	lst_len;
	char	**cmd_av;
	t_token	*iter;

	iter = word;
	lst_len = 0;
	while (iter)
	{
		lst_len++;
		iter = iter->next;
	}
	if (!(cmd_av = ft_memalloc((lst_len + 1) * sizeof(char*))))
		return (NULL);
	token_to_array(word, cmd_av);
	return (cmd_av);
}

void	extract_assign(t_simple_cmd *before)
{
	t_token *iter;
	t_token *words;
	t_token	*assigns;
	t_token *save;
	int		flag;

	flag = 0;
	words = NULL;
	assigns = NULL;
	iter = before->word_lst;
	while ((iter))
	{
		if (iter->type == WORD)
			flag = 1;
		save = iter->next;
		if (((iter->data.str[0] != '=')
			&& (parser_is_assign(iter))) && (!flag))
			add_token(&assigns, iter);
		else
			add_token(&words, iter);
		iter->next = NULL;
		iter = save;
	}
	before->word_lst = words;
	before->assign_lst = assigns;
}

t_cmd_tab	*expand_simple_cmd(t_simple_cmd *before)
{
	t_cmd_tab	*after;

	if (!(after = ft_memalloc(sizeof(t_cmd_tab))))
		return (NULL);
	if (expand_token_lst(before) == MEMERR)
		return (NULL);
	extract_assign(before);
	if (!(after->av = tokens_to_str(before->word_lst)))
		return (NULL);
	if (!(after->assign_lst = tokens_to_str(before->assign_lst)))
		return (NULL);
	after->redir_lst = before->redir_lst;
	return (after);
}

void		add_cmd_tab(t_cmd_tab **head, t_cmd_tab *to_add)
{
	t_cmd_tab *tmp;

	if (*head == NULL)
		*head = to_add;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		to_add->previous = tmp;
		tmp->next = to_add;
	}
}

t_cmd_tab	*expand_pipeline(t_simple_cmd *cmd_lst)
{
	t_simple_cmd	*iter;
	t_cmd_tab		*cmd_tab;
	t_cmd_tab		*head;

	iter = cmd_lst;
	head = NULL;
	while (iter)
	{
		if (!(cmd_tab = expand_simple_cmd(iter)))
			return (NULL);
		add_cmd_tab(&head, cmd_tab);
		iter = iter->next;
	}
	return (head);
}
