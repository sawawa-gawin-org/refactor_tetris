NAME = tetris

CC = gcc
CFLAGS = -lncurses

SRC_DIR = ./srcs/

OBJ_DIR = ./obj/

SRCS := tetris.c create_new_block.c destroy_old_block.c detect_reaching_top.c \
		display_board.c fall_down_auto.c has_to_update.c rotate_block.c \
		utils/display_components.c create_next_block.c
SRCS := $(addprefix $(SRC_DIR), $(SRCS)) 

# OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p obj/utils

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
