NAME = tetris

CC = gcc
CFLAGS = -lncurses
IFLAGS = -I./includes/

SRC_DIR = ./srcs/

OBJ_DIR = ./obj/
SUB_OBJ_DIR = cores utils

SRCS := main.c \
		cores/create_block.c cores/destroy_block.c cores/is_reaching_top.c \
		cores/display_screen.c cores/fall_down_block.c cores/rotate_block.c \
		utils/display_components.c utils/gettime_as_us.c
SRCS := $(addprefix $(SRC_DIR), $(SRCS)) 

OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(addprefix $(OBJ_DIR), $(SUB_OBJ_DIR))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
