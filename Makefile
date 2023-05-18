NAME = pipex
BONUS = pipex
SRC = src/pipex.c \
      src/cmd_path.c \
      src/cmd_execution.c \
      src/get_next_line.c \
      src/get_next_line_utils.c \
	  src/parsing.c
HEADERS = -I ./include
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
OBJ = $(addprefix obj/, $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# bonus: $(BONUS)

# $(BONUS): $(OBJ) $(OBJ_BONUS)
# 	$(CC) $(CFLAGS) $(OBJ) $(OBJ_BONUS) -o $(BONUS)

obj/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
