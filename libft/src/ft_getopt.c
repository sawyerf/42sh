/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 18:03:23 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/21 15:39:56 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			g_optind;

static	int		ft_char_cmp(char c, char *str)
{
	while (*str != 0)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

static	int		next_arg(char **nextchar, char **argv)
{
	if (argv[g_optind] == NULL)
		return (-1);
	*nextchar = argv[g_optind];
	if ((**nextchar != '-')
			|| ((!ft_strncmp(*nextchar, "--", 2)) && ft_strlen(*nextchar) == 2))
	{
		if (!ft_strncmp(*nextchar, "--", 2))
			g_optind++;
		return (-1);
	}
	*nextchar = *nextchar + 1;
	if (**nextchar == 0)
		return (-1);
	return (0);
}

static	void	handle_invalid(char *name, char c)
{
	write(2, name, ft_strlen(name));
	write(2, ": illegal option -- ", 20);
	write(2, &c, 1);
	write(2, "\n", 1);
}

static	int		handle_next_arg(char **nextchar, char **argv)
{
	if (next_arg(nextchar, argv) == -1)
	{
		*nextchar = NULL;
		return (-1);
	}
	return (0);
}

int				ft_getopt(char **argv, char *optstring)
{
	static char	*nextchar = NULL;
	int			ret;

	if (nextchar == NULL)
		if (handle_next_arg(&nextchar, argv) == -1)
			return (-1);
	if (*nextchar == 0)
	{
		g_optind++;
		if (handle_next_arg(&nextchar, argv) == -1)
			return (-1);
	}
	ret = 63;
	if (ft_char_cmp(*nextchar, optstring) == 1)
	{
		ret = (int)*nextchar;
		nextchar++;
	}
	else
	{
		handle_invalid(argv[0], *nextchar);
		nextchar = NULL;
	}
	return (ret);
}
