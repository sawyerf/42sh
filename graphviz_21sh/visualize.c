#include "../../sh_core.h"
#include "fcntl.h"
#include "stdio.h"

int	fd = -1;

int cmd_num = 1;
int pipe_num = 0;
int and_or_num = 1;
int		toogle = -1;
size_t semicol = 1;
char			buffer[4096];
char	*pipe_str = "PIPE";
char	*and_or_str = "AND_OR";
char	*cmd_str = "CMD";

void init_file()
{
	fd = open("treegraph.dot",O_WRONLY | O_APPEND | O_CREAT );
	char *header = "digraph AST{\n";
	write(fd, header, ft_strlen(header));
}

void	close_file()
{
	char *bottom = "}\n";

	write(fd, bottom, ft_strlen(bottom));
	close (fd);
}

void	dump_and_or(t_token *token)
{
	char op[32];
	char *to;
	int	 to_num;
	
	bzero(op, 10);
	if (token->type == AND_IF)
		ft_strcpy(op, "AND");
	else
		ft_strcpy(op, "OR");
	if (pipe_num % 2 == 0)
	{
		to = and_or_str;
		to_num = and_or_num;
		and_or_num++;
	}
	else
	{
		to = pipe_str;
		to_num = pipe_num;
		pipe_num++;
	}
	sprintf(buffer, "%s%d [label=\"%s\"];\n%s%d -> %s%d;\n",and_or_str, and_or_num, op,  and_or_str, and_or_num, to, to_num); 
	if (write(fd, buffer, strlen(buffer)) == -1)
		exit(1);
	bzero(buffer, 4096);
}

char	*joincmd(t_simple_cmd command)
{
	char *ret = "";
	t_token *iter;

	iter = command.word_lst;

	while (iter)
	{
		ret = ft_strjoin(ret, iter->data.str);
		ret = ft_strjoin(ret, " - ");
		iter = iter->next;
	}
	return (ret);
}

void	dump_pipe(t_parser *parser)
{
	pipe_num++;
	sprintf(buffer, "%s%d [label=\"|\"];\n %s%d -> %s%d;\n", pipe_str, pipe_num, pipe_str, pipe_num, and_or_str, and_or_num);
	cmd_num = 1;
	if (write(fd, buffer, strlen(buffer)) == -1)
		exit(1);
	bzero(buffer, 4096);

}

void	dump_cmd(t_parser *parser)
{
	sprintf(buffer, "%s%d [label=\"%s\"];\n %s%d -> PIPE%d;\n", cmd_str, cmd_num, joincmd(parser->cmd), cmd_str, cmd_num, pipe_num);
	cmd_num++;
	if (write(fd, buffer, strlen(buffer)) == -1)
		exit(1);
	bzero(buffer, 4096);
}

void	dump_pipe(int pipe_num)
{
	sprintf(buffer, "%s%d [label=\"|\"];\n %s%d -> %s%d;\n", pipe_str, pipe_num, pipe_str, pipe_num, and_or_str, and_or_num);
	cmd_num = 1;
	if (write(fd, buffer, strlen(buffer)) == -1)
		exit(1);
	bzero(buffer, 4096);

}

void	dump_tree(t_tree *tree)
{
	int sep_num;
	int	pipe_num;
	int and_or_num;
	int cmd_num;
	static int flag = 0;

	if (!flag){
	sep_num = 0;
	pipe_num = 0;
	and_or_num = 0;
	cmd_num = 0;
	flag = 1
	}
	if ((tree->type == SEMI_COL) || (tree->type == AMPERS))
	{
		sep_num++;
		dump_sep(sep_num);
	}
	else if ((tree->type == OR_IF) || (tree->type == AND_IF))
	{
		and_or_num++;
		dump_and_or(and_or_num);
	}
	else
	{
		pipe_num++;
		dump_pipe(pipe_num);
		dump_pipeline(tree->pipeline, pipe_num);
	}
	dump_tree(tree->left);
	dump_tree(tree->right);
	flag = 0;
}
