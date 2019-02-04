/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 22:27:00 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/01 18:21:17 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

static int	test_access(char *path, t_cmd_tab *cmd)
{
	char 	*tmp;
	int 	err_code;

	tmp = ft_strjoin(path, cmd->av[0]);
	if (tmp == NULL)
		return (MEMERR);
	if ((err_code = bin_perm(tmp)) == 0)
	{
		cmd->full_path = tmp;
		return (0);
	}
	free(tmp);
	return (err_code);
}

static	int	iter_paths(char **tab, t_cmd_tab *cmd)
{
	int		i;
	int		err_code;
	int		last_err_code;

	i = 0;
	last_err_code = BIN_NOT_FOUND;
	while (tab[i] != NULL)
	{
		add_slash(&tab[i]);
		if ((err_code = test_access(tab[i], cmd)) == MEMERR)
		{
			free_tab(tab);
			return (MEMERR);
		}
		else if (err_code == 0)
			return (0);
		if (err_code != BIN_NOT_FOUND)
		   last_err_code = err_code;	/* bin not found is default error */
		i++;
	}
	exec_error(last_err_code, cmd->av[0]);
	return (0);
}

int	bin_pathfinder(t_cmd_tab *cmd, char *path)
{
	char **path_tab;
	int	ret;

	if ((path_tab = ft_strsplit(path, ':')) == NULL)
		return (MEMERR);
	if (path_tab[0] == NULL) /* path is set but empty we search current dir*/
	{
		if ((ret = bin_perm(cmd->av[0])) == 0)
			cmd->full_path = cmd->av[0];
		else
			exec_error(ret, cmd->av[0]);
		free_tab(path_tab);
		return (ret);
	}
	else
	{
		if (iter_paths(path_tab, cmd) == MEMERR)
			return (MEMERR);
	}
	free_tab(path_tab);
	return (0);
}
