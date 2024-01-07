NAME = tetris

CC = gcc
CFLAGS = -lncurses

SRCS = tetris.c \
		/srcs/create_new_block.c /srcs/destroy_old_block.c /srcs/detect_reaching_top.c \
		/srcs/display_board.c /srcs/fall_down_auto.c /srcs/srcs/has_to_update.c /srcs/rotate_block.c

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