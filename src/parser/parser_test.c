#include "ft_lexer.h"
#include "ft_eval.h"

void	print_tree(t_ast_node *tree)
{
	char types[100][100]= {"WORD", "NEWLINE", "IO_NUM", "FILENAME", "ASSIGN", "PIPE", "SEMI_COL",
				"AMPERS", "ANDIF", "ORIF", "LESSAND", "GREATAND" , "DGREAT", "LESS", "GREAT"};
	if (!tree)
		return;
	if ((tree->type == OR_IF) || (tree->type == AND_IF) || (tree->type == SEMI_COL))
	{
		ft_printf("++++\nNODE %s\n++++\n", types[tree->type]);
	}
	else 
		test_pipeline(tree->pipeline);
	print_tree(tree->left);
	print_tree(tree->right);
}

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
	ft_printf("\t>>>>>>SIMPLE COMMAND============\n");
	ft_printf("\t\targs_lst:\n");
	print_tokens(cmd->word_lst);
	ft_printf("***************************\n");
	ft_printf("\t\tassign_lst:\n");
	print_tokens(cmd->assign_lst);
	ft_printf("***************************\n");
	ft_printf("\t\tredir_lst:\n");
	print_redir_lst(cmd->redir_lst);
	ft_printf("\t>>>>>>END OF SIMPLE COMMAND======\n");
}
void	test_pipeline(t_simple_cmd *start)
{

	ft_printf("<<<<<<<<PIPELINE>>>>>>>>\n");
	while (start)
	{
		test_simplecmd(start);
		start=  start->next;

	}
	ft_printf("<<<<<<<<END OF PIPELINE>>>>>>>>\n");
}
