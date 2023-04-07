NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3
SRCP = ./src/parsing
SRCE = ./src/execution
OBJ = obj
LIBFT = src/libft/libft.a
LIB = -lreadline -L ~/.brew/Cellar/readline/8.2.1/lib -I ~/.brew/Cellar/readline/8.2.1/include
OBJP = $(patsubst $(SRCP)/%.c, $(OBJ)/%.o, $(wildcard $(SRCP)/*.c))
OBJE = $(patsubst $(SRCE)/%.c, $(OBJ)/%.o, $(wildcard $(SRCE)/*.c))

all: $(NAME)

$(NAME):$(OBJ) $(OBJP) $(OBJE) $(LIBFT)
	$(CC) $(CFLAGS) $(LIB) $(OBJP) $(OBJE) $(LIBFT) -o $@

$(OBJ)/%.o: $(SRCP)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(SRCE)/%.c
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