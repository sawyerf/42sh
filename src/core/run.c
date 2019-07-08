/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:08:26 by apeyret           #+#    #+#             */
/*   Updated: 2019/07/08 15:25:41 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"
#include "hashtable.h"

int		run_command(char *line)
{
	int ret;

	if (!line)
		return (-1);
	if ((*line) && (ft_strcmp(line, "\n")))
	{
		if ((ret = sh_parser(line)))
			return (ret);
	}
	else
		ft_strdel(&line);
	return (0);
}

int		sh_readfile(char *prompt, char **str)
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
	if (!(tmp = ft_strjoin(line, "\n")))
		return (MEMERR);
	ft_strdel(&line);
	line = tmp;
	*str = line;
	return (0);
}

void	run_script(char *file)
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

void	shrc(void)
{
	char	*path;
	char	*home;
	int		mode;

	if (!(home = envchrr(g_sh.env, "HOME"))
		|| !(path = ft_zprintf("%s/%s", home, ".42shrc")))
		return ;
	mode = g_sh.mode;
	g_sh.mode = MODEFILE;
	run_script(path);
	ft_strdel(&path);
	g_sh.mode = mode;
}

int		readnrun(t_read_fn read_fn)
{
	int			ret;
	char		*line;

	if ((ret = read_fn(get_env_value("PS1"), &line)) == CTRL_D ||
		ret == MEMERR || ret < 0)
	{
		if (ret == MEMERR || ret < 0)
			return (ret);
		if ((ret == CTRL_D) && (exit_jobs()))
			return (1);
	}
	if (((ret = run_command(line)) == SYNERR)
			&& (g_sh.mode == MODEFILE))
		return (ret);
	if (ret == MEMERR)
	{
		ft_dprintf(STDERR_FILENO, "42sh: memory failure\n");
		g_sh.status = MEMERR;
		return (MEMERR);
	}
	return (0);
}
