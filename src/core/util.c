/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 16:10:23 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/12 22:21:15 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sh_core.h"

int			add_slash(char **path)
{
	int		len;
	char	*tmp;

	len = ft_strlen(*path);
	if ((len != 0) && ((*path)[len - 1] != '/'))
	{
		tmp = ft_strjoin(*path, "/");
		if (tmp == NULL)
			return (MEMERR);
		free(*path);
		*path = tmp;
	}
	return (0);
}

int			ft_cmptab(char **tab, char *str)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		if (!ft_strcmp(tab[i], str))
			return (i);
		i++;
	}
	return (-1);
}

void		add_cmdlst(t_command **head, t_command *to_add)
{
	t_command *tmp;

	if (*head == NULL)
	{
		*head = to_add;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = to_add;
	to_add->previous = tmp;
}

t_command	*new_cmd_node(char **space_split)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (new == NULL)
		return (NULL);
	ft_bzero(new, sizeof(t_command));
	if (space_split != NULL)
		new->args = dup_tab(space_split);
	return (new);
}

char		**dup_tab(char **tab)
{
	size_t	len;
	size_t	i;
	char	**copy;

	len = 0;
	i = 0;
	while (tab[len] != NULL)
		len++;
	copy = malloc((len + 1) * sizeof(char*));
	if (copy == NULL)
		return (NULL);
	while (i < len)
	{
		copy[i] = ft_strdup(tab[i]);
		if (copy[i] == NULL)
		{
			free_tab(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
