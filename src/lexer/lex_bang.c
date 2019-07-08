/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_bang.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:18:48 by apeyret           #+#    #+#             */
/*   Updated: 2019/07/08 20:17:14 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"
#include "readline.h"

char	*while_squote(t_str *str, char *s)
{
	while (*s)
	{
		str_putnstr(s, str, 1);
		s++;
		if (*s == '\'')
		{
			str_putc(&s, str);
			s++;
			break ;
		}
	}
	return (s);
}

char	*desactivate_bang(char *s)
{
	t_str	str;

	str.str = NULL;
	while (*s)
	{
		if (*s == '\\')
		{
			str_putnstr(s, &str, 2);
			s += 2;
		}
		else if (*s == '\'')
			s = while_squote(&str, s);
		else if (*s == '!' && !ft_cisin(" \t\n", *s) && *s)
		{
			str_putnstr("\\!", &str, 2);
			s++;
			if (*s == '!')
				str_putnstr("\\!", &str, 2);
			if (*s == '!')
				s++;
		}
		else
			str_putc(&s, &str);
	}
	return (str.str);
}

int		lenint(char *s)
{
	int		i;
	int		min;

	i = 0;
	min = 0;
	if (*s == '-')
		min++;
	while (s[i + min])
	{
		if (!ft_isdigit(s[i + min]))
			break ;
		i++;
	}
	if (!i)
		return (0);
	return (i + min);
}

int		handle_bang(t_lexer *lx_st)
{
	int		ret;
	char	c;
	char	d;

	c = lx_st->cursor[1];
	lx_st->cursor[1] = 0;
	d = cmdisin(lx_st->line);
	lx_st->cursor[1] = c;
	if (g_sh.mode != INTERACTIVE
			|| ft_cisin("\n \t", *(lx_st->cursor + 1))
			|| !*(lx_st->cursor + 1) || (d == '"' && lx_st->cursor[1] == '"'))
		return (str_putc(&(lx_st->cursor), &(lx_st->token->data)));
	else if (*(lx_st->cursor + 1) == '!')
		ret = simple_bang(lx_st);
	else
		ret = word_bang(lx_st);
	if (!ret)
		ft_printf("%s", lx_st->line);
	return (ret);
}
