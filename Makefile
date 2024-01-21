include variables.mk

ifdef DEBUG_MODE
OBJS := $(DOBJS)
CFLAGS += $(DFLAGS)
NAME := $(DNAME)
OBJ_DIR := $(DOBJ_DIR)
endif

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(addprefix $(OBJ_DIR), $(SUB_OBJ_DIR))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	$(CC) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

debug:
	make DEBUG_MODE=1

clean:
	rm -rf $(TMP_DIR) $(DNAME)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all debug clean fclean re
