/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:54:05 by ajari             #+#    #+#             */
/*   Updated: 2023/03/16 12:48:42 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <unistd.h>
# define RED "\033[0;31m"
# define BLUE "\033[36;01m"
# define GREEN "\033[0;32m"
# define WELLOW "\033[0;33m"
# define AS_DEFAULT "\033[0m"

typedef struct t_env
{
	char			*key;
	int				equals;
	char			*value;
	int				index;
	struct t_env	*next;
}					t_env;

typedef struct s_list
{
	char			**cmdsp;
	char			*cmd;
	int				infile;
	int				outfile;
	char			*limiter;
	int				stat;
	t_env			*env;
	const char		*err;
	struct s_list	*next;
}					t_list;

t_list				*g_v;

/////////////// execution //////////////////

void				sort_env(t_env **env);
void				envadd_back(t_env **lst, t_env *new);

/////////////////////////////////////////////

t_list				*ft_lstnew(char *cmd, t_env *ev);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));

//////////// parsing ////////////////////
void				add_char(char **s, char c);
void				print(char c, int color, char *str);
int					error(char c, char *str_er);
t_env				*getlstenv(char **ev);
void				fill_cmds(char *s, t_env *ev);
char				*expend(t_env *env, char *s, int i);
void				no_expend(char *s, char **dup, char c, int *i);
void				search_replace(t_env *env, char *s, char **dup, int *i);
t_env				*getlstenv(char **ev);
int					len_name(char *s);
char				*add_spc(char *s, int i, int j, char c);
int					rm_quote(t_env *env, char *s, int i, char c);
int					check_in(char *s);
/////////////////////////////////////////////
#endif
