#include "../../ft_lexer.h"

void	print_redir_lst(t_redir *start)
{
	while (start)
	{
		ft_printf("left:");
		print_token(start->left);
		ft_printf("op:\n");
		print_tokens(start->op);
		ft_printf("right\n");
		print_tokens(start->right);
		ft_printf("==========================================\n");
		start = start->next;
	}
}

void	test_simplecmd(t_simple_cmd *cmd)
{
	ft_printf(">>>>>>SIMPLE COMMAND============\n");
	ft_printf("args_lst:\n");
	print_tokens(cmd->word_lst);
	ft_printf("***************************\n");
	ft_printf("assign_lst:\n");
	print_tokens(cmd->assign_lst);
	ft_printf("***************************\n");
	ft_printf("redir_lst:\n");
	print_redir_lst(cmd->redir_lst);
	ft_printf(">>>>>>END OF SIMPLE COMMAND======\n");
}
void	test_pipeline(t_parser *parser)
{
	t_simple_cmd *start;

	start = parser->pipeline;
	while (start)
	{
		test_simplecmd(start);
		start=  start->next;

	}
}
