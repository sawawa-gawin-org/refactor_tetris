NAME = tetris
DNAME = $(addsuffix _debug, $(NAME))

HEADER_DIR = ./includes/
HEADERS := tetris.h

HEADERS := $(addprefix $(HEADER_DIR), $(HEADERS))

SRC_DIR = ./srcs/
SRCS := main.c \
		cores/create_block.c cores/destroy_block.c cores/is_reaching_bottom.c \
		cores/display_screen.c cores/put_block_bottom.c cores/rotate_block.c \
		cores/validate_screen_size.c \
		utils/display_components.c utils/gettime_as_us.c utils/sum.c
SRCS := $(addprefix $(SRC_DIR), $(SRCS)) 

TMP_DIR = ./obj/
OBJ_DIR = $(addprefix $(TMP_DIR),prod/)
DOBJ_DIR = $(addprefix $(TMP_DIR),dev/)
SUB_OBJ_DIR = cores utils

OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
DOBJS = $(patsubst $(SRC_DIR)%.c,$(DOBJ_DIR)%.o,$(SRCS))

CC = gcc
CFLAGS = -Wall -Wexta -Werror
LFLAGS = -lncurses
DFLAGS = -fdiagnostics-color=always -g3 -fsanitize=address
IFLAGS = -I$(HEADER_DIR)