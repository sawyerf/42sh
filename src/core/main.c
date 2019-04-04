/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:07:32 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/04 16:15:09 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"
#include "hashtable.h"

t_sh	g_sh;
extern t_list	*g_thash[];

static int	init_shell(char **env)
{
	g_sh.mode = MODEFILE;
	if (isatty(STDIN_FILENO))
		g_sh.mode = INTERACTIVE;
	if (!(g_sh.env = shlvl(ft_tabdup(env))))
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

static void	silence_ac_av(char ac, char **av)
{
	(void)ac;
	(void)av;
}

int			main(int ac, char **av, char **env)
{
	char		*line;
	int			ret;
	t_read_fn	read_fn;

	silence_ac_av(ac, av);
	if (init_shell(env))
		return (MEMERR);
	ht_init();
	ht_refreshall(get_env_value("PATH"));
	hstread(g_sh.env);
	read_fn = sh_readfile;
	if (g_sh.mode == INTERACTIVE)
		read_fn = readline;
	while (42)
	{
		if ((ret = read_fn("$> ", &line)) == CTRL_D ||
				ret == MEMERR || ret == -2)
			break ;
		if (((ret = run_command(line)) == SYNERR)
				&& (g_sh.mode == MODEFILE))
			break ;
		if (ret == MEMERR)
		{
			ft_dprintf(STDERR_FILENO, "21sh: memory failure\n");
			return (MEMERR);
		}
	}
	hstaddfile(g_sh.env);
	return (0);
}
