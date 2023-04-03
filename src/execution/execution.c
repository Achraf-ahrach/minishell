/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:06:29 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/02 00:54:45 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	builtins(t_list *list, int is_child)
{
	if (!ft_strcmp(ft_tolower(list->cmdsp[0]), "echo"))
		echo(list->cmdsp);
	else if (!ft_strcmp(list->cmdsp[0], "pwd"))
		pwd(is_child);
	else if (!ft_strcmp(list->cmdsp[0], "cd"))
		cd(list, is_child);
	else if (!ft_strcmp(list->cmdsp[0], "export"))
		export(list, is_child);
	else if (!ft_strcmp(list->cmdsp[0], "unset"))
		unset(list);
	else if (!ft_strcmp(list->cmdsp[0], "env"))
		env(list->env);
	else if (!ft_strcmp(list->cmdsp[0], "exit"))
		ft_exit(list);
	else
		return (0);
	if (is_child)
		exit_status(0, 1);
	return (1);
}

void	dup_pipe(t_list *list, int *pp)
{
	if (list->i_f != -2)
	{
		dup2(list->i_f, 0);
		close(pp[0]);
	}
	if (list->o_f != -2)
	{
		dup2(list->o_f, 1);
		close(pp[1]);
	}
	else
	{
		dup2(pp[1], 1);
		close(pp[0]);
		close(pp[1]);
	}
}

void	dup_file(t_list *list)
{
	if (list->i_f != -2)
		dup2(list->i_f, 0);
	if (list->o_f != -2)
		dup2(list->o_f, 1);
}

void	execution(void)
{
	t_list	*list;
	int		exit_status;
	int		pid;
	int		pp[2];
	int		k = 0;
	int		h = 0;

	list = g_v;
	k = dup(1);
	h = dup(0);
	if (ft_lstsize(list) == 1 && list->cmdsp && builtins(list, 0))
		return ;
	while (list)
	{
		if (list->next && list->stat)
		{
			pipe(pp);
			if (fork() == 0)
			{
				dup_pipe(list, pp);
				ft_child(list, NULL, NULL);
			}
			dup2(pp[0], 0);
			close(pp[1]);
			close(pp[0]);
		}
		else if (list->stat)
		{
			pid = fork();
			if (pid == 0)
			{
				dup_file(list);
				ft_child(list, NULL, NULL);
			}
		}
		list = list->next;
	}
	dup2(k, 1);
	dup2(h, 0);

	int		pid_wait;
	int i = -1;
	while (++i < ft_lstsize(g_v))
	{
		pid_wait = wait(&exit_status);
		if (pid_wait == pid)
			g_v->var->exit_status = WEXITSTATUS(exit_status);
	}
}
