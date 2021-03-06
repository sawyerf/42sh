/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_autocpl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 21:17:33 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/25 18:48:55 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_list	*get_choice(t_rdl *rdl, t_autocomplete acp)
{
	char	*path;

	if (cmdisincurs(rdl) == '\\')
		return (ft_lstnew("\\", 4));
	else if (acp.type == cmd_name)
	{
		path = get_env_value("PATH");
		return (get_exec(acp.str, path));
	}
	else if (acp.type == arg)
		return (get_folex(acp.str, &filexist));
	else if (acp.type == param)
		return (get_cplenv(acp.str));
	return (NULL);
}

int		acp_gettype(t_rdl *rdl, t_autocomplete *acp)
{
	char	c;
	int		ret;

	c = rdl->str[rdl->curs];
	rdl->str[rdl->curs] = 0;
	if ((ret = ft_light_parser(rdl->str, acp)))
	{
		rdl->str[rdl->curs] = c;
		return (ret);
	}
	rdl->str[rdl->curs] = c;
	return (0);
}

void	rdladdword(t_rdl *rdl, char *s, char c)
{
	while (*s)
	{
		if (c == 0 && *s == '\n')
		{
			rdladdstr(rdl, "\\");
			*s = 'n';
		}
		else if (ft_cisin("\t\r", *s))
		{
			rdladd(rdl, '\\');
			*s = (*s == '\r') ? 'r' : *s;
			*s = (*s == '\t') ? 't' : *s;
		}
		else if (!c && ft_cisin("&|*$'\";\\`~<>{ ", *s))
			rdladd(rdl, '\\');
		else if (c == '"' && ft_cisin("$\"\\", *s))
			rdladd(rdl, '\\');
		else if (c == '\'' && *s == '\'')
			rdladdstr(rdl, "'\\'");
		rdladd(rdl, *s);
		s++;
	}
}

void	fill_complt(t_rdl *rdl, t_list *lst)
{
	char	c;

	c = cmdisincurs(rdl);
	rdladdword(rdl, lst->content, c);
	if (lst->content_size == 0 || lst->content_size == 1)
	{
		if (c == '"' || c == '\'')
			rdladd(rdl, c);
		rdladd(rdl, ' ');
	}
	else if (lst->content_size == 3)
		rdladd(rdl, '/');
}

int		autocompl(t_rdl *rdl, char *buf)
{
	t_list			*lst;
	t_autocomplete	acp;

	(void)buf;
	if (acp_gettype(rdl, &acp))
		return (0);
	if (!(lst = get_choice(rdl, acp)))
	{
		ft_strdel(&acp.str);
		return (0);
	}
	if (!lst->next)
		fill_complt(rdl, lst);
	else if (!acp_multichc(rdl, lst))
		putlst(acp.str, lst, rdl);
	ft_strdel(&acp.str);
	ft_lstdel(&lst);
	return (0);
}
