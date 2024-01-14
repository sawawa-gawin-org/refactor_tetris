NAME = tetris

CC = gcc
CFLAGS = -lncurses
IFLAGS = -I$(HEADER_DIR)
DFLAGS = -fdiagnostics-color=always -g3 -fsanitize=address

HEADER_DIR = ./includes/
SRC_DIR = ./srcs/

OBJ_DIR = ./obj/
SUB_OBJ_DIR = cores utils

SRCS := main.c \
		cores/create_block.c cores/destroy_block.c cores/is_reaching_bottom.c \
		cores/display_screen.c cores/put_block_bottom.c cores/rotate_block.c \
		cores/validate_screen_size.c \
		utils/display_components.c utils/gettime_as_us.c utils/sum.c
SRCS := $(addprefix $(SRC_DIR), $(SRCS)) 

HEADERS := tetris.h
HEADERS := $(addprefix $(HEADER_DIR), $(HEADERS))

OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(addprefix $(OBJ_DIR), $(SUB_OBJ_DIR))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	$(CC) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

debug: $(OBJ_DIR) $(OBJS)
	$(CC) $(DFLAGS) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all debug clean fclean re
