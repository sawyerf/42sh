/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:10:23 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/26 18:37:36 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "hashtable.h"

void	fc_print(t_fc fc, t_list *lst, int i)
{
	while (lst && i)
	{
		if (!ft_cisin(fc.opt, 'n'))
			ft_printf("%-6d%s\n", lst->content_size / 10, lst->content);
		else
			ft_printf("      %s\n", lst->content);
		if (i < 0)
		{
			i++;
			lst = lst->next;
		}
		else 
		{
			i--;
			lst = lst->prev;
		}
	}
}


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
		ft_printf("Retry\n");
		ft_strdel(&file);
		hash++;
	}
	return (file);
}

int		fc_writelst(char *file, t_list *lst, int size)
{
	int				fd;
	
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
			if (!(fc->editor = ft_strdup("vim")))
				return (MEMERR);
		}
	}
	run_command(ft_zprintf("%s %s\n", fc->editor, file));
	return (g_sh.status);
}


int		fc(t_cmd_tab *cmd)
{
	t_fc	fc;
	int		mode;

	(void)cmd;
	//hstdellast();
	mode = g_sh.mode;
	if (fc_parser(cmd->av, &fc) < 0)
		return (1);
	if (ft_cisin(fc.opt, 's'))
		return (fc_s(fc));
	else if (ft_cisin(fc.opt, 'l') && ft_cisin(fc.opt, 'e'))
		return (fc_le(fc));
	else if (ft_cisin(fc.opt, 'l'))
		return (fc_l(fc));
	else
		return (fc_e(fc));
	g_sh.mode = mode;
}
