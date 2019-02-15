/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:11:09 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/15 21:56:14 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"
#include "readline.h"

void		exec_error(int errnum, char *str)
{
	if (errnum == BIN_NO_PATH)
		putstr_stderr("21sh: PATH not set");
	else if (errnum == CMD_NOT_FOUND)
		putstr_stderr("21sh: command not found: ");
	else if (errnum == BIN_PERM_DENY)
		putstr_stderr("21sh: permission denied: ");
	else if (errnum == BIN_NOT_FOUND)
		putstr_stderr("21sh: no such file or directory: ");
	else if (errnum == BIN_EXEC_ERR)
		putstr_stderr("21sh: exec error: ");
	else if (errnum == BIN_IS_DIR)
		putstr_stderr("21sh: is a directory: ");
	if (str != NULL)
		putstr_stderr(str);
	putstr_stderr("\n");
}

int			bin_perm(char *path)
{
	struct stat target;

	if (stat(path, &target) != 0)
		return (BIN_NOT_FOUND);
	if (!S_ISREG(target.st_mode))
	{
		if (S_ISDIR(target.st_mode))
				return (BIN_IS_DIR);
		return (BIN_PERM_DENY);
	}
	if (access(path, X_OK) != 0)
		return (BIN_PERM_DENY);
	return (0);
}

int			handle_full_path(char *cmd_name)
{
	int ret;

	if ((ret = bin_perm(cmd_name)) != 0)
		return (ACCERR);
	return (0);
}
void	exit_wrap(int code, t_cmd_tab *cmd)
{	
//	free_cmd_tab(cmd);
	exec_error(code, cmd->av[0]);	
	(void)cmd;
	exit(code);
}
/* execve_wrap is always inside a fork*/
static int		execve_wrap(t_cmd_tab *cmd)
{	
	char	*path;
	int		ret;

	cmd->process_env = craft_env(g_sh_state.export_var, cmd->assign_lst);
	if (cmd->process_env == NULL)
		return (MEMERR);
	if (ft_ispath(cmd->av[0]))
	{
		if (handle_full_path(cmd->av[0]) != 0)
			exit_wrap (ACCERR, cmd);
		if ((cmd->full_path = ft_strdup(cmd->av[0])) == NULL)
			exit_wrap(MEMERR, cmd);
	}
	else 
	{
		path = get_process_env("PATH", cmd->process_env);
		if (ht_getvalue(path, cmd) == MEMERR)
			return (MEMERR);
		if (!cmd->full_path)
			exit_wrap (127, cmd);	/* maybe exit ?*/
	}
	ret = execve(cmd->full_path, cmd->av, cmd->process_env); 
	putstr_stderr("21sh: bad file format\n");
	exit_wrap(ret, cmd);
	return (0);
}


void	wait_wrapper(t_cmd_tab *cmd, pid_t pid)
{
	int		wstatus;

	waitpid(pid, &wstatus, 0);	
	cmd->exit_signal = -1;
	cmd->exit_status = -1;
	if (WIFEXITED(wstatus))
	{
		cmd->exit_status = (int)WEXITSTATUS(wstatus);
	}
	else if (WIFSIGNALED(wstatus))
	{
		cmd->exit_signal = WTERMSIG(wstatus);
	}
	//ft_printf("%s exiting with status %d\n", cmd->av[0], cmd->exit_status);
}


t_bool		is_builtin(t_cmd_tab *cmd)
{
	static t_builtin	array[7] = {ft_echo, change_dir, setenv_wrapper,
							ft_unsetenv, ft_env, ft_exit};
	static	char		*builtins[] = {"echo", "cd", "setenv", "unsetenv",
							"env", "exit", NULL};
	int					i;

	if ((i = ft_cmptab(builtins, cmd->av[0])) != -1)
	{
		cmd->process_env = craft_env(ft_tabdup(g_sh_state.export_var), cmd->assign_lst);
		if (cmd->process_env == NULL)
			return (MEMERR);
		cmd->exit_status = array[i](cmd);
		ft_printf("BUILTIN:%s exited with status %d\n", cmd->av[0], cmd->exit_status);
		return (FT_TRUE);
	}
	return (FT_FALSE);
}

int		spawn_in_pipe(t_cmd_tab *cmd)
{
	if (cmd->av[0] == NULL)
		return (0);
	if (is_builtin(cmd) == FT_TRUE)
	{
		free_cmd_tab(cmd);
		return (0);
	}
	else
		return (execve_wrap(cmd));
}

static	int assign_to_shell(t_cmd_tab *cmd)
{
	int i;
	t_environ 	*tmp;
	t_environ 	*is_set;
	int			to_export;
	i = 0;
	while (cmd->assign_lst[i])
	{
		to_export = 0;
		if ((is_set = get_env_node(cmd->assign_lst[i])))
			to_export = is_set->to_export; 
		if (!(tmp = env_to_lst(cmd->assign_lst[i])))
			return (MEMERR);
		if (set_shell_env(tmp->name, tmp->value, to_export) == MEMERR)
			return (MEMERR);
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		i++;
	}
	return (0);
}

int		spawn_command(t_cmd_tab *cmd)
{
	pid_t 	pid;
	int		ret;

	if (cmd->av[0] == NULL)
		return (assign_to_shell(cmd));
	if (is_builtin(cmd) == FT_TRUE)
		return (0);
	pid = fork();
	if (pid == -1)
		return (MEMERR);
	if (pid == 0)
	{
		if ((ret = handle_redir(cmd->redir_lst)))
			return (ret);
		execve_wrap(cmd);
		exit_wrap(1, cmd); /* handle errors here*/
	}
	wait_wrapper(cmd, pid);
	return (0);

}
