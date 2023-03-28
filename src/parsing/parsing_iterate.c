/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_iterate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:11:04 by ajari             #+#    #+#             */
/*   Updated: 2023/03/28 18:02:03 by aahrach          ###   ########.fr       */
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
		return (error(": no such file or directory\n", name), *stat = 0, -1);
	if (access(name, R_OK) == -1)
		return (error(": bermission denied\n", name), *stat = 0, -1);
	fd = open(name, O_RDONLY, 777);
	return (fd);
}

int	outfd(char *name, int trunc, int *stat)
{
	int	fd;

	if (access(name, W_OK) == 0 && access(name, W_OK) == -1)
		return (error(": permission denied\n", name), *stat = 0, -1);
	if (trunc)
		fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
		fd = open(name, O_CREAT | O_WRONLY, 0777);
	return (fd);
}

int	here_doc(char *lim, char *s, int exp)
{
	int	p[2];

	pipe(p);
	if (lim && (lim[0] == '\'' || lim[0] == '\"'))
		exp = 0;
	if (fork() == 0)
	{
		while (1)
		{
			s = readline("\033[36;01mhere_doc>\033[0m");
			if (!ft_strcmp(s, rm_quote(lim, 0, 0)))
			{
				free(s);
				break ;
			}
			s = expend(s, 0, exp);
			ft_putendl_fd(s, p[1]);
			free(s);
		}
	}
	wait(0);
	close(p[1]);
	return (p[0]);
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
			t->i_f = here_doc(t->cmd[++i], 0, 1);
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
			{
				printf("%s\n", t->cmd[i]);
				t->cmd[i] = rm_quote(expend(t->cmd[i], 0, 1), 0, 0);
				printf("%s\n", t->cmd[i]);
			}
			i++;
		}
		one_cmd(t);
		t = t->next;
	}
}