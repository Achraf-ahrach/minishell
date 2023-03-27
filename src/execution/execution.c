/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:06:29 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/27 18:05:00 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

int	builtins(int is_child)
{
	if (!ft_strcmp(g_v->cmdsp[0], "echo"))
		echo(g_v->cmdsp);
	else if (!ft_strcmp(g_v->cmdsp[0], "pwd"))
		pwd(is_child);
	else if (!ft_strcmp(g_v->cmdsp[0], "cd"))
		cd();
	else if (!ft_strcmp(g_v->cmdsp[0], "export"))
		export();
	else if (!ft_strcmp(g_v->cmdsp[0], "unset"))
		unset(g_v);
	else if (!ft_strcmp(g_v->cmdsp[0], "env"))
		env(g_v->env);
	else if (!ft_strcmp(g_v->cmdsp[0], "exit"))
		ft_exit();
	else
		return (0);
	if (is_child)
		exit_status(0, 0);
	return (1);
}

void	dup_pipe(t_list *list, int *pp)
{
	if (list->i_f != -1)
		dup2(list->i_f, 0);
	if (list->o_f != -1)
		dup2(pp[1], 1);
	//close(pp[0]);
	//close(pp[1]);
}

void	dup_file(t_list *list)
{
	if (list->i_f != -1)
		dup2(list->i_f, 0);
	if (list->o_f != -1)
		dup2(list->o_f, 0);
}

void	execution()
{
	t_list	*list;
	int		exit_status;
	int		i;
	int		pp[2];

	list = g_v;
	if (ft_lstsize(list) == 1 && !builtins(0))
		return;
	else
	{
		while (list)
		{
			if (list->next && list->stat)
			{
				pipe(pp);
				if (fork() == 0)
				{
					dup_pipe(list, pp);
					ft_child(list);
				}
				close(pp[1]);
				close(pp[0]);
				dup2(pp[1], 0);
			}
			else if (list->stat)
			{
				if (fork() == 0)
				{
					dup_file(list);
					ft_child(list);
				}
			}
			list = list->next;
		}
		i = -1;
		while (++i < ft_lstsize(g_v))
			waitpid(-1, &exit_status, 0);
		g_v->var->exit_status = WEXITSTATUS(exit_status);
	}
}

// int main(int ac, char **av, char **env)
// {
// 	char	*line;
// 	char	**p;

// 	g_v = malloc(sizeof(t_list));
// 	//g_v->env =  malloc(sizeof(t_env));
// 	line = readline("minishell: ");
// 	g_v->env = getlstenv(env);
// 	printf("g_v->env->key: %s\n", g_v->env->key);
// 	return (0);
// 	printf("%s\n", g_v->env->key);
// 	p = a_split(line, ' ');
// 	g_v = malloc(sizeof(t_list));
// 	g_v->stat = 1;
// 	g_v->cmdsp = malloc(2 * sizeof(char *));
// 	//g_v->var = malloc(sizeof(t_var));
// 	g_v->next = NULL;
// 	g_v->infile = -1;
// 	g_v->outfile = -1;
// 	g_v->cmdsp[0] = ft_strdup(p[0]);
// 	//g_v->cmdsp[1] = ft_strdup(p[1]);
// 	g_v->cmdsp[1] = NULL;
// 	execution();
// }
