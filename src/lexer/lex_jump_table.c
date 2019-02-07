/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_jump_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/07 19:08:59 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "readline.h"
#include "ft_lexer.h"
/*
add mem error exit for str_putchar done
add lex error for backslash followed by EOI
*/


int	handle_dquote(t_lexer *lexer_state)
{
	if (*(lexer_state->cursor) == '"')
	{
		if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
			return (MEMERR);
	}
	while (*(lexer_state->cursor))
	{
		if (*(lexer_state->cursor) == '"')
		{
			if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
				return (MEMERR);
			return (handle_common(lexer_state));
		}
		else if ((*(lexer_state->cursor) == '\\') && (*(*&(lexer_state->cursor) + 1)))
		{
			if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
				return (MEMERR);
		}
		if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
			return (MEMERR);
	}

	return (DQUOTE_ERR);
}

int handle_squote(t_lexer *lexer_state)
{
	char *new_line;

	while (42)
	{

		if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
			return (MEMERR);
		if (*(lexer_state->cursor) == '\'')
		{
			if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
				return (MEMERR);
			return (0);
		}
		else if (*(lexer_state->cursor) ==  '\0')
		{
			new_line = readline("> ");
			if (new_line == NULL)
				return (MEMERR);
			else if (*new_line == 0)
				return (SQUOTE_ERR);
			free(lexer_state->line);
			lexer_state->line = new_line;
			(lexer_state->cursor) = new_line;
		}
	}

	return (SQUOTE_ERR);
}

int	handle_digit(t_lexer *lexer_state)
{
	static	char	*ops = "|&><;";

	while (*(lexer_state->cursor))
	{
		if ((ft_is_whitespace(*(lexer_state->cursor))) || (ft_strchr(ops, *(lexer_state->cursor))))
		{
			if (ft_strchr("><", *(lexer_state->cursor)))
				lexer_state->token->type = IO_NUM;
			break;
		}
		else if (!ft_isdigit(*(lexer_state->cursor)))
			return(handle_common(lexer_state));
		if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
			return (MEMERR);
	}
	return (0);
}

int	handle_param_exp(t_lexer *lexer_state)
{
	if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
		return (MEMERR);
	if (*(lexer_state->cursor) == '{')
	{
		if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
			return (MEMERR);
		if (*(lexer_state->cursor) == '}')
			return (BAD_SUB);
		while (*(lexer_state->cursor))
		{
			if (!parser_is_name_c(*(lexer_state->cursor)))
				break;
			if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
				return (MEMERR);
		}
		if (*(lexer_state->cursor) == 0)
			return (INCOMPLETE_SUB);
		if (*(lexer_state->cursor) != '}')
			return (BAD_SUB);
		if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
			return (MEMERR);
	}
	return (0);
}

int	handle_common(t_lexer *lexer_state)
{
	int				err_ret;
	static	char	*ops = "|&><;";

	err_ret = 0;
	while (*(lexer_state->cursor))
	{
		if ((ft_is_whitespace(*(lexer_state->cursor))) || (ft_strchr(ops, *(lexer_state->cursor))))
			break;
		if (*(lexer_state->cursor) == '"')
			err_ret = handle_dquote(lexer_state);
		else if (*(lexer_state->cursor) == '\'')
			err_ret = handle_squote(lexer_state);
		else if (*(lexer_state->cursor) == '$')
			err_ret = handle_param_exp(lexer_state);
		else if ((*(lexer_state->cursor) == '\\') && (*(*&(lexer_state->cursor) + 1)))
		{
			if ((str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
				|| (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR))
				return (MEMERR);
		}
		else
		{
			if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
				return (MEMERR);
		}
		if (err_ret)
			return (err_ret);
	}
	return (0);
}

int	handle_semic(t_lexer *lexer_state)
{
	lexer_state->token->type = SEMI_COL;
	if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
		return (MEMERR);
	return (0);
}	

int	handle_column(t_lexer *lexer_state)
{
	if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
		return (MEMERR);
	if (*(lexer_state->cursor) == '|')
	{
		if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
			return (MEMERR);
		lexer_state->token->type = OR_IF;
	}
	else
		lexer_state->token->type = PIPE;
	return (0);
}	

int	handle_ampersand(t_lexer *lexer_state)
{
	if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
		return (MEMERR);
	if (*(lexer_state->cursor) == '&')
	{
		if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
			return (MEMERR);
		lexer_state->token->type = AND_IF;
	}
	else
		lexer_state->token->type = AMPERS;
	return (0);
}	

int	handle_great(t_lexer *lexer_state)
{
	if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
		return (MEMERR);
	lexer_state->token->type = GREAT;
	if (*(lexer_state->cursor) == '>')
	{
		if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
			return (MEMERR);
		lexer_state->token->type = DGREAT;
	}
	else if (*(lexer_state->cursor) == '&')
	{
		if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
			return (MEMERR);
		lexer_state->token->type = GREATAND;
	}
	return (0);
}

int handle_less(t_lexer *lexer_state)
{
	if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
		return (MEMERR);
	lexer_state->token->type = LESS;
	if (*(lexer_state->cursor) == '&')
	{
		if (str_putchar(&(lexer_state->cursor), &(lexer_state->token->data)) == MEMERR)
			return (MEMERR);
		lexer_state->token->type = LESSAND;
	}
/*	else if (iter[1] == '<')
	{
		iter++;
		lexer_state->token->type = DLESS; //heredoc
	}*/
	return (0);
}
