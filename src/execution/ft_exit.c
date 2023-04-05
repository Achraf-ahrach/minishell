/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:46:02 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/05 11:41:37 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	exit_status(int exit_status, int x)
{
	g_v->var->exit_status = exit_status;
	if (x)
		exit (exit_status);
}

int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit_exit(t_list *list)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(list->cmdsp[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit_status(255, 1);
}

void	ft_exit(t_list *list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!list->cmdsp[1])
		exit_status(0, 1);
	else if (!str_isdigit(list->cmdsp[1]))
		ft_exit_exit(list);
	else if (str_isdigit(list->cmdsp[1]) && list->cmdsp[2])
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		exit_status(1, 1);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		exit_status(ft_atoi(list->cmdsp[1]), 1);
	}
}
