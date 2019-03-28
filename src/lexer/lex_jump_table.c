/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_jump_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/03/28 14:50:26 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "ft_lexer.h"

int		request_new_line(t_lexer *lx_st)
{
	char *new_line;
	t_read_fn read_fn;
	int ret;

	read_fn = readline;
	if (g_sh.mode != INTERACTIVE)
		read_fn = sh_readfile;
	ret = read_fn("> ", &new_line); //??????
	if (ret)
		return (ret);
/*	ft_printf("***ret is %d ptr %p\n***", ret, new_line);
	if (new_line == NULL) // should be for mem err
		return (QUOTE_ERR);
	else if (*new_line == 0)
		return (QUOTE_ERR);*/
	free(lx_st->line); // this has to change
	lx_st->line = new_line;
	lx_st->cursor = new_line;
	return (0);
}
static int	handle_backslash(t_lexer *lx_st)
{
	int ret;

	if ((str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		|| (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR))
		return (MEMERR);
	if (*(lx_st->cursor) == '\0')
	{
		if ((ret = request_new_line(lx_st)))
			return (ret);
	}
	return (0);
}


int			handle_dquote(t_lexer *lx_st)
{
	int ret;

	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	while (42)
	{
		if (*(lx_st->cursor) == '"')
			return (str_putc(&(lx_st->cursor), &(lx_st->token->data))
				== MEMERR) ? MEMERR : handle_common(lx_st);
		else if ((*(lx_st->cursor) == '\\') && (*((lx_st->cursor) + 1)))
		{
			if (handle_backslash(lx_st))
				return (MEMERR);
		}
		else if (*(lx_st->cursor) == '\0')
		{
			if ((ret = request_new_line(lx_st)))
				return (ret);
		}
		else if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
	}
	return (ENDOFINPUT);
}

int			handle_squote(t_lexer *lx_st)
{
	int ret;

	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	while (42)
	{
		if (*(lx_st->cursor) == '\'')
		{
			if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
				return (MEMERR);
			return (handle_common(lx_st));
		}
		else if (*(lx_st->cursor) == '\0')
		{
			if ((ret = request_new_line(lx_st)))
				return (ret);
		}
		else if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
	}
	return (ENDOFINPUT);
}

int			handle_digit(t_lexer *lx_st)
{
	static	char	*ops = "|&><;";

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

int			handle_param_exp(t_lexer *lx_st)
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

int			handle_common(t_lexer *lx_st)
{
	while (*(lx_st->cursor))
	{
		if (ft_cisin("\n\t |&><;", *(lx_st->cursor)))
			break ;
		if (*(lx_st->cursor) == '"')
			handle_dquote(lx_st);
		else if (*(lx_st->cursor) == '\'')
			handle_squote(lx_st);
		else if (*(lx_st->cursor) == '$')
			handle_param_exp(lx_st);
		else if ((*(lx_st->cursor) == '\\') && (*((lx_st->cursor) + 1)))
		{
			if (handle_backslash(lx_st))
				return (MEMERR);
		}
		else if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
	}
	return (0);
}

int			handle_newline(t_lexer *lx_st)
{
	lx_st->token->type = NEWLINE;
	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	return (0);
}

int			handle_semic(t_lexer *lx_st)
{
	lx_st->token->type = SEMI_COL;
	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	return (0);
}

int			handle_column(t_lexer *lx_st)
{
	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	if (*(lx_st->cursor) == '|')
	{
		if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
		lx_st->token->type = OR_IF;
	}
	else
		lx_st->token->type = PIPE;
	return (0);
}

int			handle_ampersand(t_lexer *lx_st)
{
	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	if (*(lx_st->cursor) == '&')
	{
		if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
		lx_st->token->type = AND_IF;
	}
	else
		lx_st->token->type = AMPERS;
	return (0);
}

int			handle_great(t_lexer *lx_st)
{
	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	lx_st->token->type = GREAT;
	if (*(lx_st->cursor) == '>')
	{
		if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
		lx_st->token->type = DGREAT;
	}
	else if (*(lx_st->cursor) == '&')
	{
		if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
		lx_st->token->type = GREATAND;
	}
	return (0);
}

int			handle_less(t_lexer *lx_st)
{
	if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
		return (MEMERR);
	lx_st->token->type = LESS;
	if (*(lx_st->cursor) == '<')
	{
		if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
		lx_st->token->type = DLESS;
	}
	if (*(lx_st->cursor) == '&')
	{
		if (str_putc(&(lx_st->cursor), &(lx_st->token->data)) == MEMERR)
			return (MEMERR);
		lx_st->token->type = LESSAND;
	}
	return (0);
}
