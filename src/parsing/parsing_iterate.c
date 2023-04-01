/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_iterate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:11:04 by ajari             #+#    #+#             */
/*   Updated: 2023/04/01 16:17:59 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	add_arg(char *s, int *i, char ***cmd)
{
	char	*str;

	str = NULL;
	while (ft_isspace(s[*i]))
		*i += 1;
	if (s[*i] != '<' && s[*i] != '>')
	{
		while (!ft_isspace(s[*i]) && s[*i])
		{
			add_char(&str, s[*i]);
			*i += 1;
		}
		add_str(cmd, str);
	}
}

int	op(char *dir)
{
	DIR	*t;

	if (!ft_strncmp(dir, "./", 2))
	{
		t = opendir(dir);
		if (t)
		{
			closedir(t);
			return (error("Is a directory", dir));
		}
		return (1);
	}
	else
		return (1);
}

void	utilhere_doc(int *p, char *lim, int exp)
{
	char	*s;

	close(p[0]);
	while (1)
	{
		s = readline("\033[36;01mhere_doc>\033[0m");
		if (!ft_strcmp(s, rm_quote(lim)))
		{
			free(s);
			break ;
		}
		s = expend(s, 0, exp);
		ft_putendl_fd(s, p[1]);
		free(s);
	}
	close(p[1]);
	exit(0);
}

int	here_doc(char *lim, int exp)
{
	int	id;
	int	p[2];

	pipe(p);
	if (lim && (lim[0] == '\'' || lim[0] == '\"'))
		exp = 0;
	id = fork();
	if (id == 0)
		utilhere_doc(p, lim, exp);
	wait(0);
	close(p[1]);
	return (p[0]);
}

void	open_heredocs(t_list *t)
{
	int	i;

	while (t)
	{
		i = 0;
		while (t->cmd[i])
		{
			if (!ft_strcmp(t->cmd[i], "<<"))
				t->h_d = here_doc(t->cmd[i + 1], 1);
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
		while (t->cmd[i])
		{
			if (!ft_strcmp(t->cmd[i], "<") && op(rm_quote(t->cmd[i + 1])))
				t->i_f = infd(t->cmd[++i], &t->stat);
			else if (!ft_strcmp(t->cmd[i], "<<") && ++i)
				t->i_f = t->h_d;
			else if (!ft_strcmp(t->cmd[i], ">") && op(rm_quote(t->cmd[i + 1])))
				t->o_f = outfd(t->cmd[++i], 1, &t->stat);
			else if (!ft_strcmp(t->cmd[i], ">>") && op(rm_quote(t->cmd[i + 1])))
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
