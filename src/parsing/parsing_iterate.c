/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_iterate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:11:04 by ajari             #+#    #+#             */
/*   Updated: 2023/04/08 17:43:27 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	op(char *dir, int *stat)
{
	DIR	*t;

	if (!ft_strncmp(dir, "./", 2) || !ft_strncmp(dir, "/", 1))
	{
		t = opendir(dir);
		free(dir);
		if (t)
		{
			closedir(t);
			g_v->var->exit_status = 126;
			return (error("Is a directory", dir), *stat = 0, 0);
		}
		return (1);
	}
	free(dir);
	return (1);
}

void	utilhere_doc(int *p, char *lim, int exp)
{
	int		k;
	char	*s;

	k = 0;
	close(p[0]);
	while (1)
	{
		signal(SIGINT, sigint_herdoc);
		s = readline("\033[36;01mhere_doc>\033[0m");
		if (!s)
			break ;
		if (!ft_strcmp(s, lim))
		{
			free(s);
			break ;
		}
		s = expend(s, 0, exp, &k);
		ft_putendl_fd(s, p[1]);
		free(s);
	}
	close(p[1]);
	exit_status(0, 1);
}

int	here_doc(char *lim, int exp, int *st)
{
	int		i;
	pid_t	id;
	int		p[2];

	pipe(p);
	i = 0;
	while (lim[i])
	{
		if ((lim[i] == '\'' || lim[i] == '\"'))
			exp = 0;
		i++;
	}
	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == 0)
		utilhere_doc(p, rm_quote(lim), exp);
	waitpid(id, st, 0);
	if (*st == 256)
		exit_status(1, 0);
	close(p[1]);
	return (p[0]);
}

void	open_heredocs(t_list *t)
{
	int	i;
	int	st;

	st = 0;
	count_heredoc(t);
	while (t && !st)
	{
		i = 0;
		while (t->cmd[i] && !st)
		{
			if (!ft_strcmp(t->cmd[i], "<<"))
			{
				if (t->h_d > 2)
					close(t->h_d);
				t->h_d = here_doc(t->cmd[i + 1], 1, &st);
			}
			i++;
		}
		t = t->next;
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
			if (!ft_strcmp(t->cmd[i], "<") && close_fd(t->i_f))
				t->i_f = infd(&t->cmd[++i], &t->stat);
			else if (!ft_strcmp(t->cmd[i], "<<") && ++i && close_fd(t->i_f))
				t->i_f = t->h_d;
			else if (!ft_strcmp(t->cmd[i], ">") && close_fd(t->o_f))
				t->o_f = outfd(&t->cmd[++i], 1, &t->stat);
			else if (!ft_strcmp(t->cmd[i], ">>") && close_fd(t->o_f))
				t->o_f = outfd(&t->cmd[++i], 0, &t->stat);
			else if (t->cmdsp || op(rm_quote(ft_strdup(t->cmd[i])), &t->stat))
				add_str(&t->cmdsp, rm_quote(t->cmd[i]));
			i++;
		}
		t = t->next;
	}
}
