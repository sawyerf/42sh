/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 20:59:59 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/27 19:58:44 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "sh_core.h"
#include <unistd.h>
#include <pwd.h>

t_prompt	g_prompt[] =\
{
	{'u', &pr_gene},
	{'W', &pr_w},
	{'w', &pr_w},
	{'h', &pr_gene},
	{'n', &pr_gene},
	{'v', &pr_version},
	{'s', &pr_version},
	{0, &pr_gene}
};

void	prpt(char *ps, t_stri *str)
{
	int		i;

	while (*ps)
	{
		if (*ps == '\\')
		{
			if (!*ps)
				return ;
			ps++;
			i = 0;
			while (g_prompt[i].p)
			{
				if (g_prompt[i].p == *ps)
					g_prompt[i].f(str, *ps);
				i++;
			}
		}
		else
			str_add(str, *ps);
		ps++;
	}
}

char	*prompt(char *ps1)
{
	t_stri	str;

	if (!ps1)
		return (ft_strdup("$> "));
	str_init(&str);
	prpt(ps1, &str);
	if (!str.size)
	{
		ft_strdel(&str.str);
		return (ft_strdup("$> "));
	}
	return (str.str);
}
