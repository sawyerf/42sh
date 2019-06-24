/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <ktlili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:07:32 by ktlili            #+#    #+#             */
/*   Updated: 2019/06/24 17:53:30 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"
#include "prompt.h"
#include "hashtable.h"

t_sh			g_sh;
extern t_list	*g_thash[];
/*
void		*malloc(size_t i)
{
	if (!(i % 3))
		return (NULL);
	return (valloc(i));
}*/

static int	init_shell(char **env, t_read_fn *read_fn, char **av)
{
	g_sh.mode = MODEFILE;
	if (isatty(STDIN_FILENO))
		g_sh.mode = INTERACTIVE;
	if (!(g_sh.env = ft_tabdup(env)))
		return (MEMERR);
	if (shlvl(&g_sh.env))
		return (MEMERR);
	if (!(g_sh.local = ft_tabnew(0)))
		return (MEMERR);
	if (!(g_sh.alias = ft_tabnew(0)))
		return (MEMERR);
	if (dup2(STDIN_FILENO, FDSAVEIN) == -1)
		return (-1);
	if (dup2(STDOUT_FILENO, FDSAVEOUT) == -1)
		return (-1);
	if (dup2(STDERR_FILENO, FDSAVEERR) == -1)
		return (-1);
	g_sh.fd = 0;
	g_sh.status = 0;
	g_sh.av = av + 1;
	g_sh.lastback = 0;
	ht_init();
	ht_refreshall(get_env_value("PATH"));
	hstread(g_sh.env);
	*read_fn = sh_readfile;
	if (g_sh.mode == INTERACTIVE)
		*read_fn = readline;
	if ((g_sh.mode == INTERACTIVE) && (init_jobctl() == SH_ABORT))
	{
		global_del();
		return (SH_ABORT);
	}
	return (0);
}

void		global_del(void)
{
	hstaddfile(g_sh.env);
	ht_del();
	ft_tabdel(&g_sh.local);
	ft_tabdel(&g_sh.alias);
	ft_tabdel(&g_sh.env);
}

void		shrc(void)
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

int			main(int ac, char **av, char **env)
{
	char		*line;
	int			ret;
	t_read_fn	read_fn;

	(void)av[ac];
	if (init_shell(env, &read_fn, av))
	{
		ft_dprintf(STDERR_FILENO, "21sh: init_shell: memory failure\n");
		global_del();
		return (MEMERR);
	}
	shrc();
	while (42)
	{
		clean_jobs();
		if ((ret = read_fn(get_env_value("PS1"), &line)) == CTRL_D ||
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
// // LOGGER   ---------------------------------------------------------------
// 	logger_close();
}
