/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:06:29 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/29 11:54:20 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

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
	//printf("in = %d\nout = %d\n", list->i_f, list->o_f);
	if (list->i_f != -2)
		dup2(list->i_f, 0);
	if (list->o_f != -2)
		dup2(pp[1], 1);
	//close(list);
	close(pp[0]);
	close(pp[1]);
}

void	dup_file(t_list *list)
{
	//printf("in = %d\nout = %d\n", list->i_f, list->o_f);
	if (list->i_f != -1)
		dup2(list->i_f, 0);
	if (list->o_f != -1)
		dup2(list->o_f, 1);
	//close(list->i_f);
	//close(list->o_f);
}

void	execution(void)
{
	t_list	*list;
	int		exit_status;
	int		i;
	int		pp[2];

	printf("\n\n\n\n\n\n\n");
	list = g_v;
	if (ft_lstsize(list) == 1 && list->cmdsp && builtins(0))
		return ;
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
