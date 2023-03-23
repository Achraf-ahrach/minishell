/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:06:29 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/22 14:45:38 by aahrach          ###   ########.fr       */
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
		cd(is_child);
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
		exit_status(0);
	return (1);
}

void	dup_pipe(t_list *list, int *pp)
{
	if (list->infile > 0)
	{
		close(pp[0]);
		dup2(0, list->infile);
	}
	else
		dup2(0, pp[0]);
	if (list->outfile > 0)
	{
		dup2(1, list->outfile);
	}
}

void	dup_file(t_list *list)
{
	if (list->infile > 0)
		dup2(0, list->infile);
	if (list->outfile > 0)
		dup2(1, list->outfile);
}

void	execution(char **env)
{
	t_list	*list;
	int		exit_status;
	int		i;
	int		pp[2];

	i = 0;
	getlstenv(env);
	g_v->next = NULL;
	list = g_v;
	if (ft_lstsize(list) == 1)
	{
		if (builtins(0))
			exit(0);
	}
	while (list)
	{
		if (list->next)
		{
			pipe(pp);
			if (list->stat != -1)
			{
				if (fork() == 0)
				{
					dup_pipe(list, pp);
					ft_child(list, pp);
				}
				close(pp[1]);
				dup2(pp[0], 0);
			}
		}
		else
		{
			if (list->stat != -1)
			{
				if (fork() == 0)
				{
					dup_file(list);
					ft_child(list, pp);
				}
			}
		}
		list = list->next;
	}
	while (i < ft_lstsize(g_v))
	{
		waitpid(-1, &exit_status, 0);
		i++;
	}
	g_v->var->exit_status = WEXITSTATUS(exit_status);
}

int main(int argc, char **av, char **env)
{
	char line
	readline("minishell: ");
	(void)argc;
	g_v = malloc(sizeof(t_list));
	g_v->cmdsp = malloc(3 * sizeof(char *));
	g_v->var = malloc(sizeof(t_var));
	g_v->cmdsp[0] = ft_strdup(av[1]);
	g_v->cmdsp[1] = ft_strdup(av[2]);
	g_v->cmdsp[2] = NULL;
	g_v->next = malloc(sizeof(t_list));
	g_v->next->next = NULL;
	g_v->stat = 1;
	g_v->next->cmdsp = malloc(3 * sizeof(char *));
	g_v->cmdsp[0] = ft_strdup(av[4]);
	g_v->cmdsp[1] = ft_strdup(av[5]);
	g_v->cmdsp[2] = NULL;
	g_v->next->stat = 1;
	//printf("=> %p\n", g_v->next->next);
	//g_v->cmdsp[1] = av[2];
	//g_v->cmdsp[2] = av[3];
	g_v->next->infile = open(av[7], O_WRONLY, 0777);
	g_v->next->outfile = -1;
	g_v->infile = -1;
	g_v->outfile = -1;
	if(g_v->next->infile < 0)
		exit(127);
	execution(env);
	//printf("exit_status = %d\n", g_v->var->exit_status);
}