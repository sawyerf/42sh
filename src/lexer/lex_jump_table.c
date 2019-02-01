/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_jump_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:53:12 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/01 14:10:04 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"
/*
add mem error exit for str_putchar done
add lex error for backslash followed by EOI
*/


int	handle_dquote(char **input, t_token *token)
{
	if (**input == '"')
	{
		if (str_putchar(input, &(token->data)) == MEMERR)
			return (MEMERR);
	}
	while (**input)
	{
		if (**input == '"')
		{
			if (str_putchar(input, &(token->data)) == MEMERR)
				return (MEMERR);
			return (handle_common(input, token));
		}
		else if ((**input == '\\') && (*(*input + 1)))
		{
			if (str_putchar(input, &(token->data)) == MEMERR)
				return (MEMERR);
		}
		if (str_putchar(input, &(token->data)) == MEMERR)
			return (MEMERR);
	}
	return (DQUOTE_ERR);
}

int handle_squote(char **input, t_token *token)
{
	while (**input)
	{
		if (str_putchar(input, &(token->data)) == MEMERR)
			return (MEMERR);
		if (**input == '\'')
		{
			if (str_putchar(input, &(token->data)) == MEMERR)
				return (MEMERR);
			return (0);
		}
	}
	return (SQUOTE_ERR);
}

int	handle_digit(char **input, t_token *token)
{
	static	char	*ops = "|&><;";

	while (**input)
	{
		if ((ft_is_whitespace(**input)) || (ft_strchr(ops, **input))
				|| (!ft_isdigit(**input)))
		{
			if (ft_strchr("><", **input))
				token->type = IO_NUM;
			break;
		}
		if (str_putchar(input, &(token->data)) == MEMERR)
			return (MEMERR);
	}
	return (0);
}

int	handle_param_exp(char **input, t_token *token)
{
	if (str_putchar(input, &(token->data)) == MEMERR)
		return (MEMERR);
	if (**input == '{')
	{
		if (str_putchar(input, &(token->data)) == MEMERR)
			return (MEMERR);
		if (**input == '}')
			return (BAD_SUB);
		while (**input)
		{
			if (!parser_is_name_c(**input))
				break;
			if (str_putchar(input, &(token->data)) == MEMERR)
				return (MEMERR);
		}
		if (**input == 0)
			return (INCOMPLETE_SUB);
		if (**input != '}')
			return (BAD_SUB);
		if (str_putchar(input, &(token->data)) == MEMERR)
			return (MEMERR);
	}
	return (0);
}

int	handle_common(char **input, t_token *token)
{
	int				err_ret;
	static	char	*ops = "|&><;";

	err_ret = 0;
	while (**input)
	{
		if ((ft_is_whitespace(**input)) || (ft_strchr(ops, **input)))
			break;
		if (**input == '"')
			err_ret = handle_dquote(input, token);
		else if (**input == '\'')
			err_ret = handle_squote(input, token);
		else if (**input == '$')
			err_ret = handle_param_exp(input, token);
		else if ((**input == '\\') && (*(*input + 1)))
		{
			if ((str_putchar(input, &(token->data)) == MEMERR)
				|| (str_putchar(input, &(token->data)) == MEMERR))
				return (MEMERR);
		}
		else
		{
			if (str_putchar(input, &(token->data)) == MEMERR)
				return (MEMERR);
		}
		if (err_ret)
			return (err_ret);
	}
	return (0);
}

int	handle_semic(char **input, t_token *token)
{
	token->type = SEMI_COL;
	if (str_putchar(input, &(token->data)) == MEMERR)
		return (MEMERR);
	return (0);
}	

int	handle_column(char **input, t_token *token)
{
	if (str_putchar(input, &(token->data)) == MEMERR)
		return (MEMERR);
	if (**input == '|')
	{
		if (str_putchar(input, &(token->data)) == MEMERR)
			return (MEMERR);
		token->type = OR_IF;
	}
	else
		token->type = PIPE;
	return (0);
}	

int	handle_ampersand(char **input, t_token *token)
{
	if (str_putchar(input, &(token->data)) == MEMERR)
		return (MEMERR);
	if (**input == '&')
	{
		if (str_putchar(input, &(token->data)) == MEMERR)
			return (MEMERR);
		token->type = AND_IF;
	}
	else
		token->type = AMPERS;
	return (0);
}	

int	handle_great(char **input, t_token *token)
{
	if (str_putchar(input, &(token->data)) == MEMERR)
		return (MEMERR);
	token->type = GREAT;
	if (**input == '>')
	{
		if (str_putchar(input, &(token->data)) == MEMERR)
			return (MEMERR);
		token->type = DGREAT;
	}
	else if (**input == '&')
	{
		if (str_putchar(input, &(token->data)) == MEMERR)
			return (MEMERR);
		token->type = GREATAND;
	}
	return (0);
}

int handle_less(char **input, t_token *token)
{
	if (str_putchar(input, &(token->data)) == MEMERR)
		return (MEMERR);
	token->type = LESS;
	if (**input == '&')
	{
		if (str_putchar(input, &(token->data)) == MEMERR)
			return (MEMERR);
		token->type = LESSAND;
	}
/*	else if (iter[1] == '<')
	{
		iter++;
		token->type = DLESS; //heredoc
	}*/
	return (0);
}
