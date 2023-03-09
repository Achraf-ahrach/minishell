/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:21:13 by ajari             #+#    #+#             */
/*   Updated: 2023/03/09 18:49:38 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define RED "\033[0;31m"
# define BLUE "\033[36;01m"
# define GREEN "\033[0;32m"
# define WELLOW "\033[0;33m"
# define AS_DEFAULT "\033[0m"

size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
void				ft_bzero(void *s, size_t n);
char				**ft_split(char const *s, char c);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
int					ft_strncmp(const char *s1, const char *s2, unsigned int n);
int					ft_strcmp(char *s1, char *s2);
char				*ft_itoa(int n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);

typedef struct t_env
{
	char			*key;
	char			*value;
	struct t_env	*next;
}					t_env;

typedef struct s_list
{
	char			**cmdsp;
	char			*cmd;
	char			**envir;
	int				infile;
	int				outfile;
	char			*limiter;
	//int				is_d;
	int				stat;
	t_env			*env;
	const char *err; //  standard error 2
	struct s_list	*next;
}					t_list;

t_list				*list;

t_list				*ft_lstnew(char *cmd, char **ev, t_env *env);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));

enum				TOKEN
{
	HEREDOC,
	INFILE,
	OUTFILE,
	COMMAND,
	ARG,
};

void				print(char c, int color, char *str);
int					error(char c, char *str_er);
t_env				*getlstenv(char **ev);

#endif
