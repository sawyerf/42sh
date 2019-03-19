/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:07:32 by ktlili            #+#    #+#             */
/*   Updated: 2019/03/19 18:30:48 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"

t_sh	g_sh;

static int	init_shell(char **env)
{
	g_sh.mode = NONINTERACTIVE;
	if (isatty(STDIN_FILENO))
		g_sh.mode = INTERACTIVE;
	if (!(g_sh.env = shlvl(dup_tab(env))))
		return (MEMERR);
	if (!(g_sh.local = ft_tabnew(0)))
		return (MEMERR);
	if (dup2(STDIN_FILENO, FDSAVEIN) == -1)
		return (-1);	
	if (dup2(STDOUT_FILENO, FDSAVEOUT) == -1)
		return (-1);
	if (dup2(STDERR_FILENO, FDSAVEERR) == -1)
		return (-1);
	g_sh.fd = 0;
	return (0);
}

static void		silence_ac_av(char ac, char **av)
{
	(void)ac;
	(void)av;
}

int		run_command(char *line)
{
	if (!line)
		return (-1);
	if ((*line) && (ft_strcmp(line, "\n")))
	{

		if (sh_parser_refac(line) == MEMERR)
			return (MEMERR);
	}
	else if (*line != '\n')
	{
		ft_strdel(&line);
		return (-1);
	}
	return (0);
}

/*
#define READSZ 1024
char *sh_readfile(char *prompt)
{
	char	 	*buffer;
	char		*data;
	char		*tmp;
	int			ret;
	int 		counter;

	(void)prompt;
	counter = 0;
	data = NULL;
	while ((ret = get_next_line(g_sh.fd, &buffer)) > 0)
	{
		ft_printf(buffer);
		if (data)
		{
			if (!(tmp = ft_strjoin(data, "\n")))
				return (NULL);
			ft_strdel(&data);
			data = tmp;
		}
		if (!(tmp = ft_strjoin(data, buffer)))
			return (NULL);
		ft_strdel(&data);
		ft_strdel(&buffer);
		data = tmp;
		counter = ret + counter; 
		if (counter > 1024)//for testing with /dev/random
			break; 
	}
	return (data);
}*/

char	*sh_readfile(char *prompt)
{
	char	*line;

	(void)prompt;
	if (get_next_line(g_sh.fd, &line) > 0)
	{
		hstadd(line);
		return (line);
	}
	return (NULL);
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
		if (!(line = readline("$> ")))
			break;
		if (run_command(line) < 0)
			write(STDOUT_FILENO, "\n", 1);
	}
	close(g_sh.fd);
	g_sh.fd = fd;
}

int				main(int ac, char **av, char **env)
{
	char	*line;
	int		ret;
	t_read_fn	read_fn;


	silence_ac_av(ac, av);
	if (init_shell(env)) // dispatcher here
		return (MEMERR);
	ht_init();
	ht_refreshall(get_env_value("PATH"));
	hstread(g_sh.env);
	read_fn = sh_readfile;
	if (g_sh.mode == INTERACTIVE)
		read_fn = readline;
	while (42)
	{
		if (!(line = read_fn("$> ")))
			break;
		if (run_command(line) < 0)
			write(STDOUT_FILENO, "\n", 1);
	}
	hstaddfile(g_sh.env);
	ret = 1;
	return (ret);
}
