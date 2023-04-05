/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:26:32 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/05 12:27:17 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	sigint(int sig)
{
	(void)sig;
	//printf("ja lhna 2\n");
	g_v->var->exit_status = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	//rl_redisplay();
	rl_redisplay();
}

void	sigquit_childe(int sig)
{
	(void)sig;
	//dprintf(2, "ja \n");
	exit_status(131, 1);
}

void	sigint_herdoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	//rl_redisplay();
	exit_status(1, 1);
}

void	sigint_childe(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	//rl_redisplay();
	exit_status(130, 1);
}