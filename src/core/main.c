/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:07:32 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/14 15:59:59 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"
#include "hashtable.h"

t_sh			g_sh;
extern t_list	*g_thash[];

static int	init_shell(char **env, t_read_fn *read_fn)
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
	g_sh.status = 0;
	ht_init();
	ht_refreshall(get_env_value("PATH"));
	hstread(g_sh.env);
	*read_fn = sh_readfile;
	if (g_sh.mode == INTERACTIVE)
		*read_fn = readline;
	return (0);
}

static void	silence_ac_av(char ac, char **av)
{
	(void)ac;
	(void)av;
}

void		global_del(void)
{
	hstaddfile(g_sh.env);
	ht_del();
	ft_tabdel(&g_sh.local);
	ft_tabdel(&g_sh.env);
}

void		sig_exit(int sig)
{
	exit_wrap(sig, NULL);
}

int			main(int ac, char **av, char **env)
{
	char		*line;
	int			ret;
	t_read_fn	read_fn;

	silence_ac_av(ac, av);
	if (init_shell(env, &read_fn))
		return (MEMERR);
	while (42)
	{
		if ((ret = read_fn("$> ", &line)) == CTRL_D ||
				ret == MEMERR || ret < 0)
			break ;
		if (((ret = run_command(line)) == SYNERR)
				&& (g_sh.mode == MODEFILE))
			break ;
		if (ret == MEMERR)
		{
			ft_dprintf(STDERR_FILENO, "21sh: memory failure\n");
			global_del();
			return (MEMERR);
		}
	}
	global_del();
	return (g_sh.status);
}
