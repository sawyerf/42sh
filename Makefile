# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apeyret <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/10 18:24:48 by apeyret           #+#    #+#              #
#    Updated: 2019/04/15 21:48:52 by apeyret          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		21sh 

CC =		clang	

CFLAGS =	-I inc/ -I lib/inc/ -Wall -Werror -Wextra -ggdb

INC_DIR =	inc

INC_FILE =	ft_eval.h					\
			ft_lexer.h					\
			ft_lexer_typedef.h			\
			ft_light_parser.h			\
			ft_light_parser_typedef.h	\
			ft_parser.h					\
			ft_parser_typedef.h			\
			ft_wordexp.h				\
			generic_typedef.h			\
			readline.h					\
			hashtable.h					\
			sh_core.h

SRC_DIR =	src

SRC_FILE =	builtins/cd_l_p.c			\
			builtins/cd_tools.c			\
			builtins/changedir.c		\
			builtins/echo.c				\
			builtins/exit.c				\
			builtins/fc.c				\
			builtins/fc_opt.c			\
			builtins/fc_range.c			\
			builtins/fc_parser.c		\
			builtins/hash.c				\
			builtins/setenv.c			\
			builtins/unset.c			\
			builtins/parser_tools.c		\
			core/clean_path.c			\
			core/env_handler.c			\
			core/ft_env.c				\
			core/ft_env_tools.c			\
			core/main.c					\
			core/path_tools.c			\
			core/util.c					\
			core/util2.c				\
			core/envadd.c				\
			core/env.c					\
			core/envdel.c				\
			core/run.c					\
			eval/redir_tools.c			\
			eval/expansion_wrappers.c	\
			eval/spawn_tools.c			\
			eval/eval_pipe.c			\
			eval/eval.c					\
			eval/spawn_bin.c			\
			eval/craft_env.c			\
			eval/handle_redir.c			\
			eval/redir_handle_right.c   \
			eval/spawn_tools_2.c		\
			eval/pre_execution.c		\
			eval/expansion_tools.c		\
			wordexp/expansion_util_3.c	\
			wordexp/expansion_util_2.c	\
			wordexp/expansion_util.c	\
			wordexp/field_split.c		\
			wordexp/ft_wordexp.c		\
			wordexp/param_expand.c		\
			wordexp/quote_removal.c		\
			wordexp/tilde_expand.c		\
			wordexp/field_split_tools.c \
			lexer/ft_realloc.c			\
			lexer/lex_jump_table.c		\
			lexer/lexer.c				\
			lexer/lexer_tools.c			\
			lexer/rev_lex.c				\
			lexer/memerror.c			\
			lexer/lex_quotes.c			\
			lexer/lex_op.c				\
			lexer/token_tools.c			\
			parser/parser_tools_2.c		\
			parser/parser_free_fn.c		\
			parser/parser_ast.c			\
			parser/refactor_parser.c	\
			parser/parser_cmd_misc.c	\
			parser/parser_complete_cmd.c\
			parser/parser_expect_and_or.c\
			parser/parser_simple_cmd.c	\
			parser/parser_expect_redir.c\
			parser/parser_tools.c		\
			parser/sh_parser.c			\
			parser/parser_heredoc.c		\
			parser/light_parser.c		\
			hashtable/hashtable.c		\
			hashtable/ht_files.c		\
			hashtable/ht_spawnbin.c		\
			readline/cmdisin.c			\
			readline/env_autoclp.c		\
			readline/files.c			\
			readline/files_right.c		\
			readline/history.c			\
			readline/hst_file.c			\
			readline/hst_use.c			\
			readline/k_autocpl.c		\
			readline/k_ctrlr.c			\
			readline/k_history.c		\
			readline/k_move.c			\
			readline/k_other.c			\
			readline/k_return.c			\
			readline/k_visual.c			\
			readline/k_visualmove.c		\
			readline/keys.c				\
			readline/move.c				\
			readline/print_choice.c		\
			readline/readline.c			\
			readline/signal.c			\
			readline/struct_rdl.c		\
			readline/struct_rdladd.c	\
			readline/termget.c			\
			readline/terminit.c			\
			readline/tools.c			

OBJ_DIR =	.obj
OBJ_FILE =	$(SRC_FILE:.c=.o)

CRT_DIR =	core 						\
		 	builtins 					\
		 	wordexp 					\
		 	lexer 						\
		 	eval 						\
		 	readline 					\
		 	parser 						\
		 	hashtable 

SRC = 		$(addprefix $(SRC_DIR)/,$(SRC_FILE))
INC = 		$(addprefix $(INC_DIR)/,$(INC_FILE))
OBJ = 		$(addprefix $(OBJ_DIR)/,$(OBJ_FILE))
CRT = 		$(addprefix $(OBJ_DIR)/,$(CRT_DIR))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) Makefile
	@printf "\033[0;32m[21sh] Compilation [o.]\033[0;0m\r"
	@mkdir -p $(CRT) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;32m[21sh] Compilation [.o]\033[0;0m\r"

norm:
	@norminette $(SRC)
	@norminette $(INC)

$(NAME): $(OBJ)
	@printf "\033[0;32m[21sh] Compilation [OK]\033[0;0m\n"
	@make -C lib/
	@$(CC) $(CFLAGS) -ltermcap $(DEBUG) $(OBJ) lib/libft.a -o $(NAME)

clean:
	@make clean -C lib/
	@/bin/rm -f $(OBJ)
	@/bin/rm -rf $(OBJ_DIR)
	@printf "\033[0;31m[21sh] Deleted *.o\033[0;0m\n"

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f lib/libft.a
	@printf "\033[0;31D[21sh] Deleted 21sh\033[0;0m\n"

re: fclean all

.PHONY: all clean fclean re
