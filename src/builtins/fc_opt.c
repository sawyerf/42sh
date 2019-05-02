/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_opt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:00:46 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/04 20:14:39 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "readline.h"

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

int		fc_l(t_fc fc)
{
	t_list	*beg;
	int		i;

	if (fc_rangel(fc, &beg, &i))
		return (0);
	fc_print(fc, beg, i);
	return (0);
}

int		fc_e(t_fc fc)
{
	char	*file;
	t_list	*beg;
	int		i;

	i = 1;
	hstdellast();
	if (fc_rangee(fc, &beg, &i))
		return (0);
	if (!(file = fc_filename(beg, i)))
		return (1);
	fc_writelst(file, beg, i);
	if (run_editor(&fc, file))
	{
		unlink(file);
		ft_strdel(&file);
		return (1);
	}
	if (ft_cisin(fc.opt, 'e'))
		run_script(file);
	unlink(file);
	ft_strdel(&file);
	return (0);
}

int		fc_le(t_fc fc)
{
	char	*file;
	t_list	*beg;
	int		i;

	i = 1;
	if (fc_rangele(fc, &beg, &i))
		return (0);
	if (!(file = fc_filename(beg, i)))
		return (1);
	fc_writelst(file, beg, i);
	run_command(fc_read(file));
	unlink(file);
	ft_strdel(&file);
	return (0);
}

int		fc_s(t_fc fc)
{
	t_list	*lst;
	char	*pre;
	char	*tmp;

	pre = NULL;
	hstdellast();
	if ((lst = gethst()) && fc.range[0])
		lst = hst_getcmp(lst, fc.range[0]);
	if (!lst && (ft_dprintf(2, "fc:history specification out of range\n") || 1))
		return (0);
	if (fc.by && fc.to && !((pre = ft_replace(lst->content, fc.to, fc.by))))
		return (MEMERR);
	else if (!pre && !(pre = ft_strdup(lst->content)))
		return (MEMERR);
	hstadd(pre);
	if (!(tmp = ft_strjoin(pre, "\n")))
		return (MEMERR);
	ft_strdel(&pre);
	ft_printf("\33[0;34m%s\33[0;0m", tmp);
	g_sh.mode = NONINTERACTIVE;
	run_command(tmp);
	return (0);
}
