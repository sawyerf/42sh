/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_jump_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/04/11 22:01:53 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "ft_lexer.h"

int	request_new_line(t_lexer *lx_st)
{
	t_read_fn	read_fn;
	char		*new_line;
	int			ret;

	read_fn = readline;
	if (g_sh.mode == NONINTERACTIVE)
		return (CTRL_D);
	if (g_sh.mode != INTERACTIVE)
		read_fn = sh_readfile;
	ret = read_fn("> ", &new_line);
	if (ret)
		return (ret);
	free(lx_st->line);
	lx_st->line = new_line;
	lx_st->cursor = new_line;
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

int	handle_param_exp(t_lexer *lx_st)
{
	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	if (*(lx_st->cursor) == '{')
	{
		if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
		if (*(lx_st->cursor) == '}')
			return (BAD_SUB);
		while (*(lx_st->cursor))
		{
			if (!parser_is_name_c(*(lx_st->cursor)))
				break ;
			if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
				return (MEMERR);
		}
		if (*(lx_st->cursor) == 0)
			return (INCOMPLETE_SUB);
		if (*(lx_st->cursor) != '}')
			return (BAD_SUB);
		if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
	}
	return (0);
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
		else if (*(lx_st->cursor) == '$')
		{
			if ((ret = handle_param_exp(lx_st)))
				return (ret);
		}
		else if (*(lx_st->cursor) == '\\')
		{
			if ((ret = handle_backslash(lx_st)))
				return (ret);
		}
		else if ((ft_cisin("\n\t |><;", *(lx_st->cursor)))
			|| (!ft_strncmp(lx_st->cursor, "&&", 2)))
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
