/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:26:32 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/08 15:39:25 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	sigint(int sig)
{
	(void)sig;
	g_v->var->exit_status = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit_childe(int sig)
{
	(void)sig;
	exit_status(131, 0);
}

void	sigint_herdoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit_status(1, 1);
}

void	sigint_childe(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	exit_status(130, 0);
}
