# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktlili <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/10 23:32:37 by ktlili            #+#    #+#              #
#    Updated: 2018/10/13 01:14:09 by ktlili           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh 

SRC_PATH = src/core

SRC_NAME =	main.c \
			util.c \
			util2.c \
			clean_path.c \
			execute.c \
			changedir.c \
			spawn_bin.c \
			env_handler.c \
			env_lst_util2.c \
			ft_env.c \
			ft_env_tools.c \
			expand_tokens.c \
			cd_l_p.c \
			cd_tools.c \
			expand_dollar.c \
			env_lst_util.c \
			path_tools.c \
			bin_path.c \
			dynamic_buff.c

LEX_PATH = src/lexer

SRC_LEX =	lexer.c \
			lex_jump_table.c \
			ft_realloc.c \
			memerror.c \

PARSER_PATH = src/parser

SRC_PARSER = parser_rules.c sh_parser.c parser_tools.c parser_test.c

WORDEXP_PATH = src/ft_wordexp

SRC_WORDEXP =	ft_wordexp.c \
				tilde_expand.c \
				field_split.c \
				param_expand.c \
				quote_removal.c \
				expansion_util.c

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o) $(SRC_LEX:.c=.o) $(SRC_WORDEXP:.c=.o) $(SRC_PARSER:.c=.o)

LIB = ./lib/libft.a

FLAGS = -Wall -g -Wextra -Werror

LFLAGS =  

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CC = clang

all:	$(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./lib/
	$(CC) $(LFLAGS) $(OBJ) $(LIB) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(OBJ_PATH)
	$(CC) -I. $(FLAGS) -o $@ -c $<

$(OBJ_PATH)/%.o: $(LEX_PATH)/%.c
	mkdir -p $(OBJ_PATH)
	$(CC) -I. $(FLAGS) -o $@ -c $<

$(OBJ_PATH)/%.o: $(WORDEXP_PATH)/%.c
	mkdir -p $(OBJ_PATH)
	$(CC) -I. $(FLAGS) -o $@ -c $<

$(OBJ_PATH)/%.o: $(PARSER_PATH)/%.c
	mkdir -p $(OBJ_PATH)
	$(CC) -I. $(FLAGS) -o $@ -c $<

clean:
	$(MAKE) -C ./lib/ clean
	/bin/rm -f $(OBJ)
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	$(MAKE) -C ./lib/ fclean
	/bin/rm -f $(NAME)

re: fclean all
