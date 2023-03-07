CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRC = ft_atoi.c\
	ft_itoa.c\
	ft_bzero.c\
	ft_split.c\
	ft_memset.c\
	ft_strlen.c\
	ft_strchr.c\
	ft_substr.c\
	ft_calloc.c\
	ft_strdup.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_strlcat.c\
	ft_strncmp.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_strmapi.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_strtrim.c\
	ft_isalpha.c\
	ft_tolower.c\
	ft_isdigit.c\
	ft_toupper.c\
	ft_isprint.c\
	ft_strjoin.c\
	ft_memmove.c\
	ft_strlcpy.c\
	ft_striteri.c\
	ft_putnbr_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putchar_fd.c
SRCB = ft_lstadd_back_bonus.c\
	ft_lstnew_bonus.c\
	ft_lstlast_bonus.c\
	ft_lstsize_bonus.c\
	ft_lstclear_bonus.c\
	ft_lstadd_front_bonus.c
OBJ = $(SRC:.c=.o)
OBJB = $(SRCB:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@ar -r $(NAME) $?

bonus : $(OBJB)
	@ar -r $(NAME) $?

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf *.o

fclean : clean
	@rm -rf $(NAME)

re : fclean all
