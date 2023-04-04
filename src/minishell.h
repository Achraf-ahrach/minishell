/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 08:31:44 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/04 19:54:14 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <sys/wait.h>
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
	int				i_f;
	int				o_f;
	int				h_d;
	int				stat;
	t_env			*env;
	t_var			*var;
	struct s_list	*next;
}					t_list;

t_list				*g_v;

void	rl_replace_line(const char *text, int clear_undo);

/////////////// execution //////////////////

void				sort_env(t_env **env);
int					len_equal(char *s);
char				*get_env(t_env *env);
void				envadd_back(t_env **lst, t_env *new);
t_env				*env_new(char *s1, char *s2);
int					builtins(t_list *list, int is_child);
void				pwd(int is_child);
void				echo(char **cmd);
void				export(t_list *list, int is_childe);
void				export_add(t_list *list, char *key, char *value);
void				check_identifier(char *str, int is_childe, int i);
void				sort_export(t_env *env, int j, int size);
int					ft_lstsize_env(t_env *env);
void				execution();
void				cd(t_list *list, int is_childe);
void				cd_oldpwd(t_env *env, int *eror);
void				cd_home(t_env *env, int *eror);
void				chang_pwd_oldpwd(char *oldpwd);
void				unset(t_list *list);
void				env(t_env *env);
void				printf_list(t_list *t);
void				ft_exit(t_list *list);
void				exit_status(int exit_status, int x);
void				ft_child(t_list *list, char *comand, char *path);
void				childe(t_list *list, pid_t *pid);
char				**ft_env(t_env *env);
char				*join_cmd(char *s1, char *s2);
char				**a_split(char const *s, char c);
char				*strjoin_a(char const *s1, char const *s2);
int					ft_error(char *one, char *two, char *thre, int new_line);

//////////// parsing ////////////////////
void				add_char(char **s, char c);
void				add_str(char ***s, char *str);
void				iterate_cmds(t_list *lst, int i);
void				print(char c, int color, char *str);
int					error(char *str_er, char *name);
t_env				*getlstenv(char **ev);
void				fill_cmds(char *s, t_env *ev, t_var *var);
char				*expend(char *s, int i, int exp, int *fd);
void				no_expend(char *s, char **dup, char c, int *i);
void				search_replace(int *fd, char *s, char **dup, int *i);
t_env				*getlstenv(char **ev);
int					len_name(char *s, int *j);
char				*add_spc(char *s, int i);
char				*rm_quote(char *s);
int					check_in(char *s);
int					infd(char *name, int *stat);
int					outfd(char *name, int trunc, int *stat);
void				lstfree(t_list *list);
int					add_chars(char **dup, char *s, int fre);
void				sig_handler_crl_(int sig);
void				sig_handler_crl(int sig);
void				sig_handler_crl__(int sig);
/////////////////////////////////////////////
#endif
