#include "ft_eval.h"


int	extract_last_tok(t_cmd_tab *pipeln)
{
	int i;

	i = 0;
	while (pipeln->next)
		pipeln = pipeln->next;
	if (!pipeln->av[0])
		return (0);
	while (pipeln->av[i + 1])
		i++;	
	if (!(g_sh.lastpara = ft_strdup(pipeln->av[i])))
		return (MEMERR);
	return (0);
}

int	launch_pipe(t_ast_node *tree, t_job *job)
{
	t_cmd_tab	*cmd_tab;
	int			ret;

	ret = 0;
	if ((!job) && (!(job = make_job(1))))
		return (MEMERR);
	if ((!(job->cmd_ln))
			&& (!(job->cmd_ln = make_cmdline(tree->start, tree->end, 0))))
		return (MEMERR);
	if (!(cmd_tab = expand_pipeline(tree->pipeline)))
		return (MEMERR);
	if ((job->fg) && (extract_last_tok(cmd_tab)))
		return (MEMERR);
	if (cmd_tab->next)
		ret = eval_pipe(cmd_tab, job);
	else
		ret = launch_command(cmd_tab, job);
	if (WIFEXITED(job->status))
	{
		tree->exit_status = (int)WEXITSTATUS(job->status);
		del_job(job);
	}
	g_sh.status = tree->exit_status;
	free_cmd_tab_lst(cmd_tab);
	return (ret);
}
