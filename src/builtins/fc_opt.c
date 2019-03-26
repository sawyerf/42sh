/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_opt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:00:46 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/26 18:37:55 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"

int		fc_l(t_fc fc)
{
	t_list	*lst;
	t_list	*tmp;
	t_list	*beg;
	int		i;

	lst = gethst();
	if (!lst || !lst->next)
		return (0);
	lst = lst->next;
	if (fc.range[0])
	{
		beg = hst_getcmp(lst, fc.range[0]);
		if (fc.range[1])
			lst = hst_getcmp(lst, fc.range[1]);
	}
	else
	{
		if ((int)lst->content_size / 10 - 10 < 0)
			beg = hst_getcmp(lst, "1");
		else
			beg = hst_getcmp(lst, ft_itoa((int)lst->content_size / 10 - 10));
	}
	if (!lst || !beg)
	{
		ft_dprintf(2, "fc: history specification out of range\n");
		return (0);
	}
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
	t_list	*tmp;
	t_list	*beg;
	int		i;

	i = 1;
	hstdellast();
	lst = gethst();
	if (!lst)
		return (0);
	beg = lst;
	if (fc.range[0])
	{
		beg = hst_getcmp(lst, fc.range[0]);
		if (fc.range[1])
		{
			if (!(lst = hst_getcmp(lst, fc.range[1])))
			{
				ft_dprintf(2, "fc: history specification out of range\n");
				return (0);
			}
			i = lst->content_size / 10 - beg->content_size / 10;
			i += (i < 0 ? -1 : 1);
		}
		if (ft_cisin(fc.opt, 'r'))
		{
			tmp = lst;
			lst = beg;
			beg = tmp;
		}
	}
	if (!beg)
	{
		ft_dprintf(2, "fc: history specification out of range\n");
		return (0);
	}
	if (!(file = fc_filename(beg, i)))
		return (1);
	fc_writelst(file, beg, i);
	if (run_editor(&fc, file))
		return (1);
	if (ft_cisin(fc.opt, 'e'))
		run_script(file);
	unlink(file);
	ft_strdel(&file);
	return (0);
}


int		fc_le(t_fc fc)
{
	char	*file;
	t_list	*lst;
	t_list	*beg;
	int		i;

	i = 1;
	lst = gethst();
	if (!lst || !lst->next)
		return (0);
	lst = lst->next;
	beg = lst;
	if (fc.range[0])
	{
		beg = hst_getcmp(lst, fc.range[0]);
		if (fc.range[1])
		{
			lst = hst_getcmp(lst, fc.range[1]);
			i = lst->content_size / 10 - beg->content_size / 10;
			i += (i < 0 ? -1 : 1);
		}
	}
	if (!(file = fc_filename(beg, i)))
		return (1);
	fc_writelst(file, beg, i);
	run_command(fc_read(file));
	ft_strdel(&file);
	unlink(file);
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
