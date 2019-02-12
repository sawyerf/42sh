/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:07:32 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/12 18:30:27 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"

t_environ **g_environ = NULL;

static int		init_g_env(char **env)
{
	t_environ	*shlvl;
	char		*newlvl;
	int			lvl;

	if (((g_environ = ft_memalloc(sizeof(t_environ*))) == NULL)
			|| (env_tab_to_lst(env, g_environ) != 0))
	{
		dispatch_parse_err(MEMERR);
		return (MEMERR);
	}
	if ((shlvl = get_env_node("SHLVL")) == NULL)
		return (set_shell_env("SHLVL", "1", 1));
	lvl = ft_atoi(shlvl->value);
	if ((lvl < 0) || ((lvl + 1) < 0))
		lvl = 0;
	newlvl = ft_itoa(lvl + 1);
	if (newlvl == NULL)
		return (MEMERR);
	if (set_shell_env("SHLVL", newlvl, 1) != 0)
	{
		free(newlvl);
		return (MEMERR);
	}
	free(newlvl);
	return (0);
}

static void		silence_ac_av(char ac, char **av)
{
	(void)ac;
	(void)av;
}

void	print_token(t_token *t)
{
	char types[100][100] = {"WORD","NEWLINE","IO_NUM","FILENAME", "ASSIGN", "PIPE", "SEMI_COL",
				"AMPERS","ANDIF", "ORIF", "LESSAND", "GREATAND", "DGREAT", "LESS",
				"GREAT"};
	if (!t)
	{
		ft_printf("NULL\n");
		return;
	}
	ft_printf("type %s |  str '%s'\n", types[t->type], t->data.str);
}

void	print_tokens(t_token *t)
{
	while (t)
	{
		print_token(t);
		t = t->next;
	}
}

void	expansion_tester(t_token *start)
{
	while (start)
	{
		if (ft_wordexp(start, FALSE) == MEMERR)
		{ft_printf("wordexp memerr\n");exit(1);}		
		start = start->next;
	}
}

int				main(int ac, char **av, char **env)
{
	char	*line;
	int		ret;
	t_token	*tok;

	silence_ac_av(ac, av);
	ht_init();
	if ((init_g_env(env) != 0))
		return (MEMERR);
	ht_refreshall(get_env_value("PATH"));
	while (42)
	{
		line = readline("$> ");
		if ((*line) && (*line != '\n'))
		{
			tok = ft_tokenizer(line);
			if (tok) 
			{
				test_sh_parser(tok);
				free_token_lst(tok);
			}
		}
		else if (*line != '\n')
			write(STDOUT_FILENO, "\n", 1);
//		free(line);
	}
	ret = 1;
//	free(line);
	write(1, "\n", 1);
	return (ret);
}
