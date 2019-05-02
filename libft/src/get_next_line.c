/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:45:19 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/12 16:02:43 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strnjoin(char **s1, char *s2, int n)
{
	char	*str;
	int		len;

	if (!s2)
		return (NULL);
	len = ft_strlen(*s1);
	if (!(str = ft_strnew(len + n)))
		return (NULL);
	str = ft_strcpy(str, *s1);
	str = ft_strncat(str, s2, n);
	ft_strdel(s1);
	return (str);
}

int			get_next_line(const int fd, char **line)
{
	static char tmp[MAX_FD][BUFF_SIZE + 1];
	char		buf[1];
	int			curs;

	curs = -1;
	if (fd < 0 || read(fd, buf, 0) == -1 || !line)
		return (-1);
	*line = NULL;
	while (42)
	{
		if (tmp[fd][0])
			*line = ft_strnjoin(line, tmp[fd], ft_strichr(tmp[fd], '\n', 0));
		if (ft_strchr(tmp[fd], '\n') || (!curs && tmp[fd][0]))
		{
			ft_strcpy(tmp[fd], &(tmp[fd][ft_strichr(tmp[fd], '\n', 1)]));
			return (2);
		}
		if (!curs)
			return ((*line && **line) ? 1 : 0);
		curs = read(fd, tmp[fd], BUFF_SIZE);
		tmp[fd][curs] = '\0';
	}
}
