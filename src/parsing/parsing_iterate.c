/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_iterate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:11:04 by ajari             #+#    #+#             */
/*   Updated: 2023/03/27 14:01:24 by aahrach          ###   ########.fr       */
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

int	infd(char *name, int *stat)
{
	int	fd;

	if (access(name, F_OK) == -1)
	{
		printf("minishell: %s :no such file or directory\n", name);
		return (*stat = 0, -1);
	}
	if (access(name, R_OK) == -1)
	{
		printf("minishell: %s :bermission denied\n", name);
		return (*stat = 0, -1);
	}
	fd = open(name, O_RDONLY, 777);
	return (fd);
}

int	outfd(char *name, int trunc, int *stat)
{
	int	fd;

	if (access(name, F_OK) == -1)
	{
		printf("minishell: %s :bermission denied\n", name);
		return (*stat = 0, -1);
	}
	if (access(name, W_OK) == -1)
	{
		printf("minishell: %s :bermission denied\n", name);
		return (*stat = 0, -1);
	}
	if (trunc)
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 777);
	else
		fd = open(name, O_CREAT | O_WRONLY, 777);
	return (fd);
}

int	here_doc(char *lim, char *s, int exp)
{
	int	p[2];

	pipe(p);
	if (lim && (lim[0] == '\'' || lim[0] == '\"'))
		exp = 0;
	else
		exp = 1;
	while (1)
	{
		s = readline("\033[36;01mhere_doc>");
		if (!ft_strcmp(s, rm_quote(lim, 0, 0)))
			return (free(s), close(p[1]), p[0]);
		s = expend(s, 0, exp);
		write(p[1], s, ft_strlen(s));
		write(p[1], "\n", 1);
		free(s);
	}
}

void	one_cmd(t_list *t)
{
	int	i;

	i = 0;
	while (t->cmd[i])
	{
		if (!ft_strcmp(t->cmd[i], "<"))
			t->i_f = infd(t->cmd[++i], &t->stat);
		else if (!ft_strcmp(t->cmd[i], "<<"))
			t->i_f = here_doc(t->cmd[++i], 0, 0);
		else if (!ft_strcmp(t->cmd[i], ">"))
			t->o_f = outfd(t->cmd[++i], 0, &t->stat);
		else if (!ft_strcmp(t->cmd[i], ">>"))
			t->o_f = outfd(t->cmd[++i], 1, &t->stat);
		else
			add_str(&t->cmdsp, t->cmd[i]);
		i++;
	}
}

void	iterate_cmds(t_list *t)
{
	int i;

	while (t)
	{
		i = 0;
		while (t->cmd && t->cmd[i])
		{
			if (i && ft_strcmp(t->cmd[i - 1], "<<"))
				t->cmd[i] = rm_quote(expend(t->cmd[i], 0, 1), 0, 0);
			i++;
		}
		one_cmd(t);
		t = t->next;
	}
}