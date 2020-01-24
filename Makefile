# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/24 18:49:21 by obanshee          #+#    #+#              #
#    Updated: 2020/01/24 18:51:16 by obanshee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -g -Wall -Wextra -Werror

LIBFTPRINTF_PATH = libftprintf/
LIBFTPRINTF = libftprintf/libftprintf.a

INC = -I includes/ -I libftprintf/includes/

SRCS_NAME = main.c 

SRCS_PATH = srcs/
OBJ_PATH  = obj/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(SRCS_NAME:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFTPRINTF_PATH)
	@gcc -o $(NAME) $(FLAGS) $(INC) $(OBJ) $(LIBFTPRINTF)

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir -p obj
	@gcc -c $(FLAGS) $(INC) $< -o $@

clean:
	@make -C $(LIBFTPRINTF_PATH)/ clean
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@make -C $(LIBFTPRINTF_PATH)/ fclean
	@/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re