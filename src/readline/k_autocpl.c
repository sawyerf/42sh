/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_autocpl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 21:17:33 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/29 17:40:02 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_list	*get_choice(t_autocomplete acp)
{
	char			*path;

	if (acp.type == cmd_name)
	{
		if (!(path = get_env_value("PATH")))
			return (NULL);
		return (get_exec(acp.str, path));
	}
	else if (acp.type == arg)
		return (get_folex(acp.str, &filexist));
	else if (acp.type == param)
		return (get_cplenv(acp.str));
	return (NULL);
}

int		autocompl(t_rdl *rdl, char *buf)
{
	char			c;
	t_list			*lst;
	t_autocomplete	acp;

	(void)buf;
	c = rdl->str[rdl->curs];
	rdl->str[rdl->curs] = 0;
	if (ft_light_parser(rdl->str, &acp))
	{
		rdl->str[rdl->curs] = c;
		return (0);
	}
	lst = get_choice(acp);
	rdl->str[rdl->curs] = c;
	if (!lst)
	{
		ft_strdel(&acp.str);
		return (0);
	}
	if (!lst->next)
	{
		rdladdstr(rdl, lst->content);
		if (lst->content_size == 0 || lst->content_size == 1)
			rdladd(rdl, ' ');
		else if (lst->content_size == 3)
			rdladd(rdl, '/');
	}
	else
		putlst(acp.str, lst, rdl);
	ft_strdel(&acp.str);
	ft_lstdel(&lst);
	return (0);
}
