#include "ft_lexer.h"

/* lexer mem error exit */


void	free_parser(t_parser *parser)
{
	free_token_lst(parser->cmd.word_lst);
	free_token_lst(parser->cmd.assign_lst);
	free_redir_lst(parser->cmd.redir_lst);
	free_token_lst(parser->head);
	free_pipeline(parser->pipeline);
//	free_list_lst(parser->list);
}

void	mem_err_exit(t_parser *parser)
{
	ft_putstr_fd("21sh: parser: memory error\n", 2);
	free_parser(parser);
}
