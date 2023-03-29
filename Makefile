NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
SRCP = src/parsing
SRCE = src/execution
OBJ = obj
LIBFT = src/libft/libft.a
LIB = -lreadline
SRCS = $(wildcard $(SRCP)/*.c $(SRCE)/*.c)
OBJS = $(patsubst $(SRCP)/%.c $(SRCE)/%.c, $(OBJ)/%.o, $(SRCS))


all: $(NAME)

$(NAME):  $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LIB) $(OBJS) $(LIBFT) -o $@

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ):
	mkdir $@

$(LIBFT):
	make all clean -C ./src/libft

fcleanlib:
	make fclean -C./src/libft

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean fcleanlib all

run: re
	@./minishell
