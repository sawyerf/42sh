/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 13:23:26 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/17 17:50:07 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "hashtable.h"
#include "readline.h"

extern char	*g_builtins[];

int		type_cmd(char *cmd, char **full)
{
	char	**paths;
	char	*path;
	int		ret;
	int		stat;

	ret = 0;
	if (ft_cisin(cmd, '/') && !exaccess(cmd))
		return (4);
	if (ft_cisin(cmd, '/'))
		return (0);
	if (ft_tabcmp(g_builtins, cmd) != -1)
		return (1);
	if (!(path = get_env_value("PATH")))
		return (0);
	if (!(paths = ft_strsplit(path, ':')))
		return (MEMERR);
	if ((*full = ft_strdup(ht_getpath(paths, cmd))))
		ret = 2;
	else if (!(stat = ht_getfile(paths, cmd, full)) || stat == br_PERMDENIED)
		ret = 3;
	else
		ft_strdel(full);
	ft_tabdel(&paths);
	return (ret);
}

void	type_msg(int stat, char *cmd, char *full)
{
	if (stat == 1)
		ft_printf("%s is a shell builtins\n", cmd);
	else if (stat == 2)
		ft_printf("%s is hashed (%s)\n", cmd, full);
	else if (stat == 3)
		ft_printf("%s is %s\n", cmd, full);
	else if (stat == 4)
		ft_printf("%s is %s\n", cmd, cmd);
	else if (stat == 0)
		ft_printf("type: %s: not found\n", cmd);
}

int		type(t_cmd_tab *cmd)
{
	int		i;
	char	*full;
	int		stat;

	i = 1;
	full = NULL;
	while (cmd->av[i])
	{
		if ((stat = type_cmd(cmd->av[i], &full)) == MEMERR)
			return (MEMERR);
		type_msg(stat, cmd->av[i], full);
		ft_strdel(&full);
		i++;
	}
	return (0);
}
