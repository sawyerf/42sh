/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:07:32 by ktlili            #+#    #+#             */
/*   Updated: 2019/03/19 20:01:19 by apeyret          ###   ########.fr       */
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

char	*sh_readfile(char *prompt)
{
	char	*line;

	(void)prompt;
	if (get_next_line(g_sh.fd, &line) > 0)
	{
		ft_printf("\33[0;34m%s\33[0;0m\n", line);
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
		//if (g_sh.status == 258)
		//	break ;
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
		//ft_printf("%d\n", g_sh.status);
	}
	hstaddfile(g_sh.env);
	ret = 1;
	return (ret);
}
