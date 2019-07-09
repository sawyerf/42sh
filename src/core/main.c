/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <ktlili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:07:32 by ktlili            #+#    #+#             */
/*   Updated: 2019/07/09 13:44:05 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"
#include "prompt.h"
#include "hashtable.h"

t_sh			g_sh;
extern t_list	*g_thash[];

static int	init_shell(char **env, t_read_fn *read_fn, char **av)
{
	ft_bzero(&g_sh, sizeof(t_sh));
	g_sh.av = av + 1;
	g_sh.mode = MODEFILE;
	if (isatty(STDIN_FILENO))
		g_sh.mode = INTERACTIVE;
	if (!(g_sh.env = ft_tabdup(env))
		|| shlvl(&g_sh.env)
		|| !(g_sh.local = ft_tabnew(0))
		|| !(g_sh.alias = ft_tabnew(0))
		|| dup2(STDIN_FILENO, FDSAVEIN) == -1
		|| dup2(STDOUT_FILENO, FDSAVEOUT) == -1
		|| dup2(STDERR_FILENO, FDSAVEERR) == -1
		|| ht_init()
		|| ht_refreshall(get_env_value("PATH")) == MEMERR)
		return (-1);
	hstread(g_sh.env);
	*read_fn = sh_readfile;
	if (g_sh.mode == INTERACTIVE)
		*read_fn = readline;
	if ((g_sh.mode == INTERACTIVE) && (init_jobctl() == SH_ABORT))
		return (SH_ABORT);
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

int			exit_jobs(void)
{
	if ((g_sh.mode == INTERACTIVE) && (g_sh.job_lst) && (!g_sh.exit_jobs))
	{
		ft_dprintf(STDERR_FILENO, "42sh: jobs still running\n");
		g_sh.exit_jobs = 2;
		return (0);
	}
	return (1);
}

int			main(int ac, char **av, char **env)
{
	t_read_fn	read_fn;

	(void)av[ac];
	if (init_shell(env, &read_fn, av))
	{
		ft_dprintf(STDERR_FILENO, "42sh: init_shell: memory failure\n");
		global_del();
		return (MEMERR);
	}
	shrc();
	while (42)
	{
		clean_jobs();
		if (readnrun(read_fn))
			break ;
		if (g_sh.exit_jobs > 0)
			g_sh.exit_jobs = g_sh.exit_jobs - 1;
	}
	global_del();
	return (g_sh.status);
}
