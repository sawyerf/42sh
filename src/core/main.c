/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:07:32 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/01 16:53:28 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"

t_environ **g_environ = NULL;

/*static void		show_prompt(void)
{
	char *pwd;

	pwd = handle_pwd_l();
	if (pwd != NULL)
	{
		ft_printf("%s", pwd);
		free(pwd);
	}
	write(1, "$> ", 3);
}*/

static int		init_g_env(char **env)
{
	t_environ	*shlvl;
	char		*newlvl;
	int			lvl;

	if (((g_environ = ft_memalloc(sizeof(t_environ*))) == NULL)
			|| (tab_to_lst(env, g_environ) != 0))
	{
		dispatch_parse_err(MEMERR);
		return (MEMERR);
	}
	if ((shlvl = get_env_node("SHLVL")) == NULL)
		return (set_shell_env("SHLVL", "1"));
	lvl = ft_atoi(shlvl->value);
	if ((lvl < 0) || ((lvl + 1) < 0))
		lvl = 0;
	newlvl = ft_itoa(lvl + 1);
	if (newlvl == NULL)
		return (MEMERR);
	if (set_shell_env("SHLVL", newlvl) != 0)
	{
		free(newlvl);
		return (MEMERR);
	}
	free(newlvl);
	return (0);
}
/*
static int		exec_loop(t_command *command_lst)
{
	t_command	*tmp;

	tmp = command_lst;
	if ((tmp != NULL) && (tmp->args != NULL))
	{
		while (tmp != NULL)
		{
			if ((execute_cmd(tmp)) == MEMERR)
			{
				free_cmdlst(command_lst);
				return (MEMERR);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}
*/
static void		silence_ac_av(char ac, char **av)
{
	(void)ac;
	(void)av;
}

void	ft_test_lexer(char *line);

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
/*
void	print_tokens(t_token *start)
{
	char types[100][100] = {"WORD","NEWLINE","IO_NUM","FILENAME", "ASSIGN", "PIPE", "SEMI_COL",
				"AMPERS","ANDIF", "ORIF", "LESSAND", "GREATAND", "DGREAT", "LESS",
				"GREAT"};
	t_token *save;
	while (start)
	{
		
		ft_printf("type %s |  str '%s'|", types[start->type], start->data.str);
		if (ft_wordexp(start) == MEMERR)
		{ft_printf("wordexp memerr\n");exit(1);}	
		ft_printf("After str '%s'", start->data.str); 
		ft_printf("\n");
		start = save;
	}
}*/

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
		if (ft_wordexp(start) == MEMERR)
		{ft_printf("wordexp memerr\n");exit(1);}		
		start = start->next;
	}
}

int				main(int ac, char **av, char **env)
{
	struct termios	save;
	char			*line;
	t_token			*tok;
	int				ret;

	silence_ac_av(ac, av);
	if ((init_g_env(env) != 0))
		return (MEMERR);
	if (!terminit(&save))
		return (1);
	//show_prompt();
	while (42)
	{
	//	ft_printf("**********************\n");
	//	ft_printf("cmdline: '%s'", line);
	//	ft_printf("**********************\n");
		line = readline("$> ");
		tok = ft_tokenizer(line);
		if (tok)
		{
	//		ft_test_lexer(line);
			test_sh_parser(tok);
	//		print_tokens(tok);
	//		ft_printf("==========================================\n");
	//		expansion_tester(tok);
	//		print_tokens(tok);
			free_token_lst(tok);
		}
		free(line);
		//show_prompt();
	}
	ret = 1;
	free(line);
	write(1, "\n", 1);
	return (ret);
}
