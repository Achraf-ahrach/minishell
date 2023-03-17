/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:46:02 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/16 19:32:22 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_exit()
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!g_v->cmdsp[1])
		exit (0);
	else if (!str_isdigit(g_v->cmdsp[1]))
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(g_v->cmdsp[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	else if (str_isdigit(g_v->cmdsp[1]) && g_v->cmdsp[2])
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		exit(1);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		exit(ft_atoi(g_v->cmdsp[1]));
	}
}