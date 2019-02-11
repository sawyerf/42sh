# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktlili <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/10 23:32:37 by ktlili            #+#    #+#              #
#    Updated: 2019/02/11 18:53:10 by apeyret          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_PATH = src

SRC_NAME =	ft_strnsplit.c \
			ft_splitblanks.c \
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
			ft_strlower.c

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o)

INC = ft_printf.h get_next_line.h libft.h

FLAGS = -Wall -Wextra -Werror 

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CC = gcc 

all:	$(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ) 
	ranlib $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(OBJ_PATH)/ft_printf
	$(CC) -I. $(FLAGS) -o $@ -c $<

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
