/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:07:32 by ktlili            #+#    #+#             */
/*   Updated: 2019/03/07 21:39:30 by ktlili           ###   ########.fr       */
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
	return (0);
}

static void		silence_ac_av(char ac, char **av)
{
	(void)ac;
	(void)av;
}

int		run_command(char *line)
{
	//t_token	*tok;

	if (!line)
		return (-1);
	if ((*line) && ft_strcmp(line, "\n"))
	{

		if (sh_parser_refac(line) == MEMERR)
			return (MEMERR);		
//		test_lexer(line);
/*		if ((tok = ft_tokenizer(line)))
		{
			sh_parser(tok);
			free_token_lst(tok);
			ft_printf("EXIT: %d\n", g_sh.last_exit);
		}*/
	}
	else if (*line != '\n')
		return (-1);
	return (0);
}

int				main(int ac, char **av, char **env)
{
	char	*line;
	int		ret;

	silence_ac_av(ac, av);
	if (init_shell(env)) // dispatcher here
		return (MEMERR);
	ht_init();
	ht_refreshall(get_env_value("PATH"));
	hstread(g_sh.env);
	while (42)
	{
		if (!(line = readline("$> ")))
			break;
		if (run_command(line) < 0)
			write(STDOUT_FILENO, "\n", 1);
		free(line);
	}
	hstaddfile(g_sh.env);
	ret = 1;
	return (ret);
}
