/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:06:29 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/05 15:52:42 by aahrach          ###   ########.fr       */
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

void	last_exit_status(pid_t pid)
{
	int		pid_wait;
	int		status;
	int		i;

	i = -1;
	while (++i < ft_lstsize(g_v))
	{
		pid_wait = wait(&status);
		if (pid_wait == pid)
		{
			g_v->var->exit_status = WEXITSTATUS(status);
			if (status == 2)
				exit_status(130, 0);
			else if (status == 3)
				exit_status(131, 0);
		}
	}
}

void	execution(void)
{
	t_list	*list;
	pid_t	pid;
	int		k;
	int		h;

	k = 0;
	h = 0;
	list = g_v;
	k = dup(1);
	h = dup(0);
	if (ft_lstsize(list) == 1 && list->cmdsp && builtins(list, 0))
		return ;
	while (list)
	{
		childe(list, &pid);
		list = list->next;
	}
	dup2(k, 1);
	dup2(h, 0);
	last_exit_status(pid);
}
