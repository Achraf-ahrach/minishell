/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_iterate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:11:04 by ajari             #+#    #+#             */
/*   Updated: 2023/04/05 15:55:55 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	op(char *dir)
{
	DIR	*t;

	dir = rm_quote(ft_strdup(dir));
	if (!ft_strncmp(dir, "./", 2))
	{
		t = opendir(dir);
		free(dir);
		if (t)
		{
			closedir(t);
			return (error("Is a directory", dir));
		}
		return (1);
	}
	free(dir);
	return (1);
}

void	utilhere_doc(int *p, char *lim, int exp)
{
	char	*s;

	close(p[0]);
	while (1)
	{
		signal(SIGINT, sigint_herdoc);
		s = readline("\033[36;01mhere_doc>\033[0m");
		if (!s)
			exit_status(0, 1);
		if (!ft_strcmp(s, rm_quote(lim)))
		{
			free(s);
			break ;
		}
		s = expend(s, 0, exp, 0);
		ft_putendl_fd(s, p[1]);
		free(s);
	}
	close(p[1]);
	exit(0);
}

int	here_doc(char *lim, int exp)
{
	int	i;
	int	id;
	int	p[2];
	int	st;

	pipe(p);
	i = 0;
	while (lim[i])
	{
		if ((lim[i] == '\'' || lim[1] == '\"'))
			exp = 0;
		i++;
	}
	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == 0)
		utilhere_doc(p, lim, exp);
	waitpid(id, &st, 0);
	st = WEXITSTATUS(st);
	if (st == 1)
		exit_status(1, 0);
	close(p[1]);
	return (p[0]);
}

void	open_heredocs(t_list *t)
{
	int	i;

	count_heredoc(t);

	while (t)
	{
		i = 0;
		while (t->cmd[i])
		{
			if (!ft_strcmp(t->cmd[i], "<<"))
				t->h_d = here_doc(t->cmd[i + 1], 1);
			i++;
		}
	}
}

void	iterate_cmds(t_list *t, int i)
{
	open_heredocs(t);

	while (t)
	{
		i = 0;
		while (t->cmd[i] && t->stat)
		{
			if (!ft_strcmp(t->cmd[i], "<") && op(t->cmd[i + 1]))
				t->i_f = infd(t->cmd[++i], &t->stat);
			else if (!ft_strcmp(t->cmd[i], "<<") && ++i)
				t->i_f = t->h_d;
			else if (!ft_strcmp(t->cmd[i], ">") && op(t->cmd[i + 1]))
				t->o_f = outfd(t->cmd[++i], 1, &t->stat);
			else if (!ft_strcmp(t->cmd[i], ">>") && op(t->cmd[i + 1]))
				t->o_f = outfd(t->cmd[++i], 0, &t->stat);
			else if (op(rm_quote(t->cmd[i])))
				add_str(&t->cmdsp, t->cmd[i]);
			i++;
		}
		if (!t->cmdsp)
			t->stat = 0;
		t = t->next;
	}
}
