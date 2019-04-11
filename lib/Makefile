# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apeyret <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/10 18:24:48 by apeyret           #+#    #+#              #
#    Updated: 2019/04/11 22:46:05 by ktlili           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = clang

CFLAGS = -I inc/ -Wall -Werror -Wextra

INC_DIR = inc

INC_FILE = get_next_line.h \
		   ft_printf.h \
		   libft.h

SRC_DIR = src

SRC_FILE =	ft_strnsplit.c \
			ft_splitblanks.c \
			ft_isalldigit.c \
			ft_util.c \
			itoa_base.c \
			ft_atoi.c \
			ft_bzero.c \
			ft_isdigit.c \
			ft_memmove.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnew.c \
			ft_toupper.c \
			ft_memcpy.c \
			ft_memset.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strdup.c \
			ft_strcpy.c \
			ft_strcat.c \
			ft_strncat.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strstr.c \
			ft_strnstr.c \
			ft_strcmp.c \
			ft_isalpha.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_tolower.c \
			ft_memalloc.c \
			ft_memdel.c \
			ft_strdel.c \
			ft_strclr.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strequ.c \
			ft_strnequ.c \
			ft_strsub.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_strsplit.c \
			ft_itoa.c \
			ft_putchar.c \
			ft_putstr.c \
			ft_putendl.c \
			ft_putnbr.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_lstnew.c \
			ft_lstdelone.c \
			ft_lstdel.c \
			ft_lstadd.c \
			ft_lstiter.c \
			ft_lstmap.c \
			get_next_line.c \
			ft_getopt.c \
			ft_printf/ft_printf.c \
			ft_printf/pf_base.c \
			ft_printf/pf_ftoa.c \
			ft_printf/pf_len.c \
			ft_printf/pf_options.c \
			ft_printf/pf_parsing.c \
			ft_printf/pf_put.c \
			ft_printf/pf_router.c \
			ft_printf/pf_struct.c \
			ft_printf/pf_utils.c \
			ft_strndup.c \
			ft_cisin.c \
			ft_tabdel.c \
			ft_strlower.c \
			ft_tabcpy.c \
			ft_tabdel.c \
			ft_tabdup.c \
			ft_tablen.c \
			ft_tabnew.c \
			ft_replace.c \
			ft_strichr.c \
			ft_strisprint.c \
			ft_rperr.c \
			ft_strisdigit.c \
			ft_tabcpy.c 


OBJ_DIR = .obj
OBJ_FILE = $(SRC_FILE:.c=.o)

CRT_DIR = ft_printf

SRC = $(addprefix $(SRC_DIR)/,$(SRC_FILE))
INC = $(addprefix $(INC_DIR)/,$(INC_FILE))
OBJ = $(addprefix $(OBJ_DIR)/,$(OBJ_FILE))
CRT = $(addprefix $(OBJ_DIR)/,$(CRT_DIR))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) Makefile
	@printf "\033[0;32m[Libft] Compilation [o.]\033[0;0m\r"
	@mkdir -p $(CRT) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;32m[Libft] Compilation [.o]\033[0;0m\r"

norm:
	@norminette $(SRC)
	@norminette $(INC)

$(NAME): $(OBJ)
	@printf "\033[0;32m[Libft] Compilation [OK]\033[0;0m\n"
	@ar rc $(NAME) $(OBJ) 
	@ranlib $(NAME)

clean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -rf $(OBJ_DIR)
	@printf "\033[0;31m[Libft] Deleted *.o\033[0;0m\n"

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
