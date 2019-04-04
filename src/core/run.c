/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:08:26 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/04 16:11:31 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"
#include "hashtable.h"

int			run_command(char *line)
{
	int ret;

	if (!line)
		return (-1);
	if ((*line) && (ft_strcmp(line, "\n")))
	{
		if ((ret = sh_parser_refac(line)))
			return (ret);
	}
	else
		ft_strdel(&line);
	return (0);
}

int			sh_readfile(char *prompt, char **str)
{
	char	*line;
	char	*tmp;
	int		ret;

	(void)prompt;
	*str = NULL;
	if ((ret = get_next_line(g_sh.fd, &line)) == -1)
		return (-1);
	if (ret == 0)
		return (1);
	hstadd(line);
	if (!(tmp = ft_strjoin(line, "\n")))
		return (MEMERR);
	ft_strdel(&line);
	line = tmp;
	ft_printf("\33[0;34m%s\33[0;0m", line);
	*str = line;
	return (0);
}

void		run_script(char *file)
{
	int		fd;
	char	*line;

	fd = g_sh.fd;
	if ((g_sh.fd = open(file, O_RDONLY)) < 0)
	{
		g_sh.fd = fd;
		return ;
	}
	while (42)
	{
		if (readline("$> ", &line))
			break ;
		if (run_command(line) == MEMERR)
			break ;
	}
	close(g_sh.fd);
	g_sh.fd = fd;
}
