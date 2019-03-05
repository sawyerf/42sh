/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:10:23 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/05 17:00:06 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"

void	fc_init(t_fc *fc)
{
	ft_bzero(fc->opt, 6);
	fc->editor = NULL;
	fc->range[0] = 0;
	fc->range[1] = 0;
}

void	fc_pprint(t_fc *fc)
{
	ft_printf("opt:       %s\n", fc->opt);
	ft_printf("editor:    %s\n", fc->editor);
	ft_printf("range[0]:  %s\n", fc->range[0]);
	ft_printf("range[1]:  %s\n", fc->range[1]);
}

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

int		fc_parser(char **av, t_fc *fc)
{
	char	c;
	int		i;

	av++;	
	c = 0;
	fc_init(fc);
	while (*av)
	{
		if (!ft_strcmp(*av, "--") || **av != '-' || ft_strisdigit(*av))
		{
			if (!ft_strcmp(*av, "--"))
				av++;
			break;
		}
		i = 1;
		while ((*av)[i])
		{
			if (ft_cisin("elnrs", (*av)[i]))
			{
				if (!ft_cisin(fc->opt, (*av)[i]))
					ft_strncat(fc->opt, *av + i, 1);
				c = (*av)[i];
			}
			else
			{
				ft_dprintf(2, "fc: -%c: invalid option\n", (*av)[i]);
				return (-1);
			}
			i++;
		}
		if (c == 'e')
		{
			av++;
			if (!*av)
			{
				ft_dprintf(2, "fc: -e: option requires an argument\n");
				return (-1);
			}
			fc->editor = ft_strdup(*av);
			av++;
			c = 0;
			continue ;
		}
		av++;
	}
	i = 0;
	while (*av)
	{
		if (i < 2)
		{
			if (!(fc->range[i] = ft_strdup(*av)))
				return (MEMERR);
			i++;
		}
		av++;
	}
	//fc_pprint(fc);
	return (0);
}

char	*fc_filename(t_list *lst, int size)
{
	int				i;
	unsigned int	hash;
	char			*file;
	char			*user;

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
	user = get_env_value("USER=");
	if (!(file = ft_zprintf("/tmp/%s%x", user, hash)))
		return (NULL);
	if (!access(file, F_OK))
	{
		ft_dprintf(2, "fc: file %s already exist\n", file);
		ft_strdel(&file);
		return (NULL);
	}
	return (file);
}

int		fc_writelst(char *file, t_list *lst, int size)
{
	int				fd;
	int				i;

	i = 0;
	fd = open(file, O_CREAT | O_WRONLY, 0600);
	if (fd < 0)
	{
		ft_dprintf(2, "fc: failed to open/create %s\n", file);
		return (-1);
	}
	while (lst && i < size)
	{
		ft_dprintf(fd, "%s\n", lst->content);
		lst = lst->next;
		i++;
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
	ft_printf("%s\n", command);
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
	return (0);
}

int		fc_l(t_fc fc)
{
	t_list	*lst;
	t_list	*tmp;
	t_list	*beg;
	int		i;

	lst = gethst();
	if (!lst)
		return (0);
	if (fc.range[0])
	{
		beg = hst_getcmp(lst, fc.range[0]);
		if (fc.range[1])
			lst = hst_getcmp(lst, fc.range[1]);
	}
	else
	{
		if ((int)lst->content_size / 10 - 10 < 0)
			beg = hst_getcmp(lst, "0");
		else
			beg = hst_getcmp(lst, ft_itoa((int)lst->content_size / 10 - 10));
	}
	if (!lst || !beg)
		return (0);
	if (ft_cisin(fc.opt, 'r'))
	{
		tmp = lst;
		lst = beg;
		beg = tmp;
	}
	i = lst->content_size / 10 - (beg->content_size / 10);
	i += (i < 0 ? -1 : 1);
	fc_print(fc, beg, i);
	return (0);
}

int		fc_e(t_fc fc)
{
	char	*file;
	t_list	*lst;
	t_list	*beg;
	int		i;

	i = 1;
	lst = gethst();
	if (fc.range[0] && !fc.range[1])
		lst = hst_getcmp(lst, fc.range[0]);
	else if (fc.range[0])
	{
		beg = hst_getcmp(lst, fc.range[1]);
		lst = hst_getcmp(lst, fc.range[0]);
		i = beg->content_size / 10 - (lst->content_size / 10);
		i += (i < 0 ? -1 : 1);
	}
	if (!(file = fc_filename(lst, 1)))
		return (1);
	fc_writelst(file, lst, i);
	run_editor(&fc, file);
	if (ft_cisin(fc.opt, 'e'))
	{
		run_command(fc_read(file));
		ft_strdel(&file);
	}
	unlink(file);
	return (0);
}

int		fc_s(t_fc fc)
{
	t_list	*lst;

	lst = gethst();
	if (fc.range[0])
		lst = hst_getcmp(lst, fc.range[0]);
	if (!lst)
		return (0);
	ft_printf("%s\n", lst->content);
	run_command(ft_strdup(lst->content));
	return (0);
}

int		fc(t_cmd_tab *cmd)
{
	t_fc	fc;

	(void)cmd;
	//hstdellast();
	if (fc_parser(cmd->av, &fc) < 0)
		return (1);
	if (ft_cisin(fc.opt, 's'))
		fc_s(fc);
	else if (ft_cisin(fc.opt, 'l'))
		fc_l(fc);
	else
		fc_e(fc);
	return (0);
}
