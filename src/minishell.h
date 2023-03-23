/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 08:31:44 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/21 18:40:21 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <unistd.h>
# define RED "\033[0;31m"
# define BLUE "\033[36;01m"
# define GREEN "\033[0;32m"
# define WELLOW "\033[0;33m"
# define AS_DEFAULT "\033[0m"

//////////////////////////////////////////
typedef struct t_env
{
	char			*key;
	int				equals;
	char			*value;
	int				index;
	struct t_env	*next;
}					t_env;       

typedef struct s_var
{
	int				exit_status;
	int				sig;
}					t_var;

typedef struct s_list
{
	char			**cmdsp;
	char			**cmd;
	int				infile;
	int				outfile;
	char			*h_d;
	int				stat;
	t_env			*env;
	t_var			*var;
	const char		*err;
	struct s_list	*next;
}					t_list;

t_list				*g_v;

/////////////// execution //////////////////

void				sort_env(t_env **env);
void				envadd_back(t_env **lst, t_env *new);
t_env				*env_new(char *s1, char *s2);
char				*pwd(int x);
void				echo(char **cmd);
void				export(void);
void				cd(void);
void				unset(t_list *list);
void				env(t_env *env);
void				ft_exit();
void				exit_status(int exit_status);
void				ft_child(t_list *list, int *pp);

//////////// parsing ////////////////////
void				add_char(char **s, char c);
void				add_str(char ***s, char *str);
void				iterate_cmds(t_list *lst);
void				print(char c, int color, char *str);
int					error(char c, char *str_er);
t_env				*getlstenv(char **ev);
void				fill_cmds(char *s, t_env *ev);
char				*expend(t_env *env, char *s, int i);
void				no_expend(char *s, char **dup, char c, int *i);
void				search_replace(t_env *env, char *s, char **dup, int *i);
t_env				*getlstenv(char **ev);
int					len_name(char *s);
char				*add_spc(char *s, int i);
int					rm_quote(t_env *env, char *s, int i, char c);
int					check_in(char *s);
/////////////////////////////////////////////
#endif
