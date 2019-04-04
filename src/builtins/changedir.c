/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changedir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 00:00:01 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/04 14:32:09 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_cdpath(char **curpath, char *cd_path)
{
	char	**cd_path_tab;
	int		ret;
	int		i;

	cd_path_tab = ft_strsplit(cd_path, ':');
	if (cd_path_tab == NULL)
		return (MEMERR);
	i = 0;
	while (cd_path_tab[i] != NULL)
	{
		if ((add_slash(&cd_path_tab[i]) == MEMERR)
			|| ((ret = dir_access(cd_path_tab[i], curpath)) == MEMERR))
		{
			free_tab(cd_path_tab);
			return (MEMERR);
		}
		if (ret == 0)
			break ;
		i++;
	}
	free_tab(cd_path_tab);
	return (0);
}

static int	handle_cdpath(char **curpath)
{
	char *cd_path;

	cd_path = get_env_value("CDPATH");
	if ((cd_path == NULL) || (*cd_path == 0))
		return (0);
	if ((ft_strncmp(*curpath, "/", 1))
			&& (ft_strncmp(*curpath, "../", 3))
				&& (ft_strncmp(*curpath, "./", 2)))
	{
		if (check_cdpath(curpath, cd_path) == MEMERR)
		{
			free(*curpath);
			return (MEMERR);
		}
	}
	return (0);
}

char		cd_parseopt(char **args)
{
	int		flag;
	char	opt;

	opt = 'L';
	g_optind = 1;
	while ((flag = ft_getopt(args, "PL")) != -1)
	{
		opt = (char)flag;
		if (opt == '?')
		{
			ft_printf("usage: cd [-LP] [dir]\n");
			break ;
		}
	}
	return (opt);
}

int			change_dir(t_cmd_tab *cmd)
{
	char	*curpath;
	char	opt;

	if ((opt = cd_parseopt(cmd->av)) == '?')
		return (0);
	if ((cmd->av[g_optind] == NULL) || (cmd->av[g_optind][0] == 0))
	{
		curpath = get_env_value("HOME");
		if ((curpath == NULL) || (*curpath == 0))
			return (cd_error(4, NULL));
		curpath = ft_strdup(curpath);
	}
	else if (!ft_strncmp(cmd->av[g_optind], "-", 2))
		curpath = ft_strdup(getoldpwd());
	else
		curpath = ft_strdup(cmd->av[g_optind]);
	if ((curpath == NULL) || (handle_cdpath(&curpath) == MEMERR))
		return (MEMERR);
	if (ft_strlen(curpath) > PATH_MAX)
		return (cd_error(1, NULL));
	if (opt == 'P')
		return (cd_p(curpath, cmd->av[g_optind]));
	else if (opt == 'L')
		return (cd_l(curpath, cmd->av[g_optind]));
	return (0);
}
