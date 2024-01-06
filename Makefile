# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: syamasaw <syamasaw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 19:32:25 by syamasaw          #+#    #+#              #
#    Updated: 2024/01/06 19:39:55 by syamasaw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = tetris

CC = gcc
CFLAGS = -lncurses

SRCS = tetris.c

OBJ_DIR = ./obj/

OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p obj

$(OBJ_DIR)%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re