/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:48:42 by apeyret           #+#    #+#             */
/*   Updated: 2019/03/25 16:16:35 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "sh_core.h"
#include "libft.h"

#define SIZE_READ 10

t_rdl	g_rdl;

int		rreadd(char *str)
{
	static char	buf[SIZE_READ + 1];
	int			ret;
	int			adv;

	if (buf[0])
	{
		adv = ft_strichr(str, '\n', 1);
		ft_strcpy(buf, &(str[adv]));
		ft_strncpy(str, buf, adv);
		return (0);
	}
	if ((ret = read(0, buf, SIZE_READ)) <= 0)
		return (ret);
	buf[ret] = 0;
	adv = ft_strichr(buf, '\n', 1);
	ft_strncpy(str, buf, adv);
	str[adv] = 0;
	ft_strcpy(buf, &(buf[adv]));
	return (1);
}

int		readline(char *prompt, char **str)
{
	char	buf[11];
	int		ret;
	int		stat;

	stat = 0;
	if (g_sh.fd)
		return (sh_readfile(prompt, str));
	setsig();
	if (!terminit(&(g_rdl.save)) || rdlinit(&g_rdl, prompt) == MEMERR)
		return (-1);
	while ((ret = rreadd(buf)) > 0)
	{
		//ft_printf("\33[1;97mrecv:%s\33[1;00m\n", buf);
		if ((stat = key_router(&g_rdl, buf)))
			break ;
	}
	if (!termreset(&(g_rdl.save)) || stat == 2)
		ft_strdel(&g_rdl.str);
	str = &g_rdl.str;
	//ft_printf("return(%d)\n", stat - 1);
	//ft_printf("str:   %s\n", *str);
	return (stat - 1);
}
