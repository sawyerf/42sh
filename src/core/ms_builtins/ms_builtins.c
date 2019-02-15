/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 13:58:59 by apeyret           #+#    #+#             */
/*   Updated: 2019/01/15 19:44:51 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ms_echo(char **av)
{
	int count;
	int nl;

	count = 0;
	nl = 1;
	av++;
	if (!av)
		return (1);
	if (av[count] && !ft_strcmp(av[count], "-n"))
	{
		nl = 0;
		av++;
	}
	while (av[count])
	{
		if (count)
			ft_putchar(' ');
		ft_putstr(av[count]);
		count++;
	}
	if (nl)
		ft_putchar('\n');
	return (0);
}

int		ms_exit(t_ast *ast, t_gvar gvar, char ***path)
{
	unsigned char nb;

	ft_printf("exit\n");
	if (!(ast->comm.opt[1]))
		nb = gvar.status;
	else if (!ft_strisdigit(ast->comm.opt[1]))
	{
		ft_printf("msh: exit: %s: numeric argument required\n",
			ast->comm.opt[1]);
		nb = 255;
	}
	else
	{
		nb = ft_atoi(ast->comm.opt[1]);
		if (ft_tablen(ast->comm.opt) > 2)
			return (ft_preturn(1,
				ft_printf("msh: exit: too many arguments\n")));
	}
	ft_tabdel(&(gvar.env));
	ft_tabdel(path);
	ms_astdel(ast);
	exit(nb);
}
