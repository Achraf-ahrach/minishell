/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 01:12:09 by ajari             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/09 15:53:40 by ajari            ###   ########.fr       */
=======
/*   Updated: 2023/03/09 09:16:01 by ajari            ###   ########.fr       */
>>>>>>> f08438e9438cfa91af561f5d6554fd8a81e3c729
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "../minishell.h"
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	ft_bzero(void *s, size_t n);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);
char	*ft_strrchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strcmp(char *s1, char *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

// typedef struct s_list
// {
// 	char			**cmdsp;
// 	char			*cmd;
// 	char			*in_f;
// 	char			*out_f;
// 	int				h_re;
// 	int				is_d;
// 	int				stat;
// 	struct s_list	*next;
// }					t_list;

<<<<<<< HEAD
// typedef struct s_list
// {
// 	char			**cmd;
// 	//char			*cmd;
// 	char			**envir;
// 	int				infile;
// 	int				outfile;
// 	char			*limiter;
// 	//int				is_d;
// 	int				stat;
// 	t_env			*env;
// 	const char *err; //  standard error 2
// 	struct s_list	*next;
// }					t_list;
=======
typedef struct s_list
{
	char			**cmdsp;
	char			*cmd;
	int				*in_f;
	int				*out_f;
	int				h_re;
	int				is_d;
	int				stat;
	struct s_list	*next;
}					t_list;
>>>>>>> f08438e9438cfa91af561f5d6554fd8a81e3c729

t_list	*ft_lstnew(char *cmd, char **ev, t_env *env);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
#endif
