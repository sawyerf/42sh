/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_jump_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <ktlili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/06/12 18:02:15 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "ft_lexer.h"

int	request_new_line(t_lexer *lx_st)
{
	t_read_fn	read_fn;
	char		*new_line;
	char		*tmp;
	int			ret;

	read_fn = readline;
	if (g_sh.mode == NONINTERACTIVE)
		return (CTRL_D);
	if (g_sh.mode != INTERACTIVE)
		read_fn = sh_readfile;
	ret = read_fn("> ", &new_line);
	if (ret || !new_line)
		return (ret);
	tmp = ft_zprintf("%s%s", lx_st->line, new_line);
	ft_strdel(&new_line);
	if (!tmp)
		return (MEMERR);
	lx_st->cursor = tmp + ft_strlen(lx_st->line);
	ft_strdel(&lx_st->line);
	lx_st->line = tmp;
	return (0);
}

int	handle_digit(t_lexer *lx_st)
{
	static	char	*ops = "|><;";

	while (*(lx_st->cursor))
	{
		if ((ft_is_whitespace(*(lx_st->cursor)))
			|| (ft_strchr(ops, *(lx_st->cursor))))
		{
			if (ft_strchr("><", *(lx_st->cursor)))
				lx_st->token->type = IO_NUM;
			break ;
		}
		else if (!ft_isdigit(*(lx_st->cursor)))
			return (handle_common(lx_st));
		if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
	}
	return (0);
}

int	valid_sup_exp(char c)
{
	if ((c == '_') || (ft_isalnum(c)) || c == ':' || c == '-' || c == '='
	|| c == '?' || c == '+' || c == '#' || c == '%')
		return (1);
	return (0);
}


int	special_params(char c)
{
	if ((c == '?') || (c == '$') || (c == '#')  || (c == '!') || (c == '-')
		|| (c == '@'))
		return (1);
	return (0);
}

int	brackets_param(t_lexer *lx_st)
{
	if ((*(lx_st->cursor) == 0) || (*(lx_st->cursor) == '}')
		|| ((!special_params(*(lx_st->cursor))) && (!valid_env_char(*(lx_st->cursor)))))
		return (BAD_SUB);
	while ((valid_sup_exp(*(lx_st->cursor))) || (special_params(*(lx_st->cursor))))
	{
		if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
	}
	if (*(lx_st->cursor) != '}')
		return (BAD_SUB);
	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);	
	return (0);
}

int	handle_param_exp(t_lexer *lx_st)
{
	int ret;

	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	if (special_params(*(lx_st->cursor)))
		return (str_putc(&(lx_st->cursor), &(lx_st->token->data)));
	if (*(lx_st->cursor) == '{')
	{
		if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
		if ((ret = brackets_param(lx_st)))
			return (ret);
	}
	return (0);
}

int	handle_common_inner(t_lexer *lx_st)
{
	int ret;

	if (*(lx_st->cursor) == '$')
	{
		if ((ret = handle_param_exp(lx_st)))
			return (ret);
	}
	else if (*(lx_st->cursor) == '\\')
	{
		if ((ret = handle_backslash(lx_st)))
			return (ret);
	}
	else if (*(lx_st->cursor) == '!')
	{
		if ((ret = handle_bang(lx_st)))
			return (ret);
	}
	else
		return (0);
	return (-1);
}


int	handle_common(t_lexer *lx_st)
{
	int ret;

	while (*(lx_st->cursor))
	{
		if ((*(lx_st->cursor) == '"') && ((ret = handle_dquote(lx_st))))
			return (ret);
		else if ((*(lx_st->cursor) == '\'') && ((ret = handle_squote(lx_st))))
			return (ret);
		else if ((ret = handle_common_inner(lx_st)))
		{
			if (ret == -1)
				continue;
			return (ret);
		}
		else if ((ft_cisin("\n\t& |><;", *(lx_st->cursor)))
			|| (!*lx_st->cursor))
			break ;
		else if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
	}
	return (0);
}

int	handle_newline(t_lexer *lx_st)
{
	lx_st->token->type = NEWLINE;
	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	return (0);
}
