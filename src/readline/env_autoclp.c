/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_autoclp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 17:28:00 by apeyret           #+#    #+#             */
/*   Updated: 2019/04/18 20:49:51 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "sh_core.h"

int		foundc(char *var, int c)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if (var[i] == c)
			return (i);
		i++;
	}
	return (0);
}

t_list	*lstnewenv(char *var, int sel)
{
	t_list	*lst;
	char	*s;

	if (!sel)
		s = ft_strndup(var, foundc(var, '='));
	else
		s = ft_zprintf("%.*s}", foundc(var, '='), var);
	lst = ft_lstnew(s, 0);
	ft_strdel(&s);
	return (lst);
}

t_list	*get_matchenv(char **env, char *match)
{
	t_list	*lst;
	int		len;
	int		i;

	if (!env)
		return (NULL);
	lst = NULL;
	len = ft_strlen(match);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(match, env[i], len))
			ft_lstadd(&lst, lstnewenv(env[i] + len, 0));
		i++;
	}
	return (lst);
}

t_list	*get_matchenvp(char **env, char *match)
{
	t_list	*lst;
	int		len;
	int		i;

	if (!env)
		return (NULL);
	lst = NULL;
	len = ft_strlen(match);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(match, env[i], len))
			ft_lstadd(&lst, lstnewenv(env[i] + len, 1));
		i++;
	}
	return (lst);
}

t_list	*get_cplenv(char *match)
{
	t_list *lst;

	match++;
	lst = NULL;
	if (*match != '{')
	{
		lst = get_matchenv(g_sh.local, match);
		ft_lstadd(&lst, get_matchenv(g_sh.env, match));
	}
	else
	{
		match++;
		lst = get_matchenvp(g_sh.local, match);
		ft_lstadd(&lst, get_matchenvp(g_sh.env, match));
	}
	return (lst);
}
