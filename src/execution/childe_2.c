/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childe_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:21:31 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/07 11:21:57 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	prror_cmd(int exit)
{
	perror("Error");
	write(2, "\n", 1);
	exit_status(exit, 1);
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

void	childe_(t_list *list, pid_t *pid)
{
	*pid = fork();
	if (*pid == 0)
	{
		dup_file(list);
		ft_child(list, NULL, NULL);
	}
}

void	childe(t_list *list, pid_t *pid)
{
	int		pp[2];

	signal(SIGINT, sigint_childe);
	signal(SIGQUIT, sigquit_childe);
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
		childe_(list, pid);
}
