/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:10:23 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/08 14:52:45 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "hashtable.h"

char	*fc_filename(t_list *lst, int size)
{
	int				i;
	unsigned int	hash;
	char			*file;

	i = 0;
	hash = 0;
	if (!lst)
		return (NULL);
	while (lst && i < size)
	{
		hash += ht_hash(lst->content);
		lst = lst->next;
		i++;
	}
	hash += ht_hash(get_env_value("USER="));
	while ((file = ft_zprintf("/tmp/%x.fc", hash)) && !access(file, F_OK))
	{
		ft_strdel(&file);
		hash++;
	}
	return (file);
}

int		fc_writelst(char *file, t_list *lst, int size)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY, 0600);
	if (fd < 0)
	{
		ft_dprintf(2, "fc: failed to open/create %s\n", file);
		return (-1);
	}
	while (lst && size)
	{
		ft_dprintf(fd, "%s\n", lst->content);
		if (size < 0)
		{
			size++;
			lst = lst->next;
		}
		else
		{
			size--;
			lst = lst->prev;
		}
	}
	close(fd);
	return (0);
}

char	*fc_read(char *file)
{
	int		fd;
	char	*line;
	char	*tmp;
	char	*command;

	command = NULL;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		if (command)
			tmp = ft_zprintf("%s\n%s", command, line);
		else
			tmp = ft_strdup(line);
		ft_strdel(&command);
		ft_strdel(&line);
		command = tmp;
	}
	close(fd);
	unlink(file);
	if (command)
		ft_printf("\33[0;34m%s\33[0;0m\n", command);
	return (command);
}

int		run_editor(t_fc *fc, char *file)
{
	char	*editor;

	if (!fc->editor)
	{
		if ((editor = get_env_value("FCEDIT=")))
		{
			if (!(fc->editor = ft_strdup(editor)))
				return (MEMERR);
		}
		else
		{
			if (!(fc->editor = ft_strdup("vi")))
				return (MEMERR);
		}
	}
	g_sh.mode = NONINTERACTIVE;
	run_command(ft_zprintf("%s %s\n", fc->editor, file));
	return (g_sh.status);
}

int		fc(t_cmd_tab *cmd)
{
	t_fc	fc;
	int		mode;
	int		ret;

	(void)cmd;
	mode = g_sh.mode;
	if (fc_parser(cmd->av, &fc) < 0)
	{
		fc_del(&fc);
		return (1);
	}
	if (ft_cisin(fc.opt, 's'))
		ret = fc_s(fc);
	else if (ft_cisin(fc.opt, 'l') && ft_cisin(fc.opt, 'e'))
		ret = fc_le(fc);
	else if (ft_cisin(fc.opt, 'l'))
		ret = fc_l(fc);
	else
		ret = fc_e(fc);
	g_sh.mode = mode;
	fc_del(&fc);
	return (ret);
}
