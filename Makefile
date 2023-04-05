NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3
SRCP = src/parsing
SRCE = src/execution
OBJ = obj
LIBFT = src/libft/libft.a
LIB = -lreadline -L ~/.brew/Cellar/readline/8.2.1/lib -I ~/.brew/Cellar/readline/8.2.1/include
OBJP = $(patsubst $(SRCP)/%.c, $(OBJ)/%.o, $(wildcard $(SRCP)/*.c))
OBJE = $(patsubst $(SRCE)/%.c, $(OBJ)/%.o, $(wildcard $(SRCE)/*.c))
OBJS = $(OBJP) $(OBJE)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LIB) $? -o $@

$(OBJ)/%.o: $(SRCP)/%.c $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(SRCE)/%.c $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ):
	mkdir $@
	@stty -echoctl

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
