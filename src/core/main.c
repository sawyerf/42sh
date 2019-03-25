/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:07:32 by ktlili            #+#    #+#             */
/*   Updated: 2019/03/25 20:40:41 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"
#include "hashtable.h"

t_sh	g_sh;
extern t_list	*g_thash[];

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
	int ret;

	if (!line)
		return (-1);
	if ((*line) && (ft_strcmp(line, "\n")))
	{
		if ((ret = sh_parser_refac(line)))
			return (ret);
	}
	else if (*line != '\n')
	{
		ft_strdel(&line);
		return (-1);
	}
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
	ft_printf("\33[0;34m%s\33[0;0m\n", line);
	hstadd(line);
	str = &line;
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
		if ((readline("$> ", &line)))
			break;
		if (run_command(line))
			break;
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
		if ((ret = read_fn("$> ", &line)) == 1 || ret == MEMERR || ret == -1)
			break;
		if (ret != 2 && run_command(line))
			break;
	}
	hstaddfile(g_sh.env);
	return (0);
}
