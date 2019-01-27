/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 07:34:37 by ktlili            #+#    #+#             */
/*   Updated: 2018/10/06 18:04:13 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_joinbuffer(char *buffer, char **line, int tocp, int *size)
{
	char *new;

	new = ft_strnew(*size + tocp);
	if (*line != NULL)
	{
		ft_memcpy(new, *line, *size);
		free(*line);
	}
	ft_memcpy(&new[*size], buffer, tocp);
	*line = new;
	*size = *size + tocp;
	return (new);
}

int		ft_seekfd(int curr_fd, t_list **head, t_list **current)
{
	t_list *lst;

	lst = *head;
	while (lst != NULL)
	{
		if (curr_fd == ((int*)lst->content)[0])
		{
			*current = lst;
			return (1);
		}
		lst = lst->next;
	}
	*current = ft_lstnew(NULL, BUFF_SIZE + 4);
	if (*current == NULL)
		return (-1);
	(*current)->content = malloc(BUFF_SIZE + 4);
	if ((*current)->content == NULL)
		return (-1);
	ft_lstadd(head, *current);
	(*current)->content_size = 4;
	*((int*)(*current)->content) = curr_fd;
	return (0);
}

int		ft_parse(t_list *file, char **line, int *total_size)
{
	char	*iter;
	int		i;

	iter = (char*)file->content + 4;
	i = 0;
	while ((i + 4) < (int)file->content_size)
	{
		if (iter[i] != '\n')
			i++;
		else
		{
			ft_joinbuffer(iter, line, i, total_size);
			if ((i + 1) < BUFF_SIZE)
				ft_memmove(iter, &iter[i + 1], file->content_size - 4 - i - 1);
			file->content_size = file->content_size - i - 1;
			return (1);
		}
	}
	ft_joinbuffer(iter, line, i, total_size);
	file->content_size = 4;
	return (0);
}

int		ft_handle_err(int fd, char **line, int *total_size)
{
	if ((fd < 0) || (line == NULL))
		return (0);
	*total_size = 0;
	*line = NULL;
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*head = NULL;
	t_list			*current;
	int				size;
	int				read_b;

	if ((!ft_handle_err(fd, line, &size)) ||
			(ft_seekfd(fd, &head, &current) == -1))
		return (-1);
	else if ((current->content_size > 4) && (ft_parse(current, line, &size)))
		return (1);
	read_b = BUFF_SIZE;
	while (read_b > 0)
	{
		read_b = read(fd, ((char*)current->content) + 4, BUFF_SIZE);
		if (read_b == -1)
			return (-1);
		else if ((read_b == 0) && (*line != NULL))
			return (1);
		else if (read_b == 0)
			return (0);
		current->content_size = read_b + 4;
		if ((ft_parse(current, line, &size) == 1) || (read_b < BUFF_SIZE))
			return (1);
	}
	return (0);
}
