/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_iterate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:11:04 by ajari             #+#    #+#             */
/*   Updated: 2023/03/29 11:55:30 by ajari            ###   ########.fr       */
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

void	utilhere_doc(int *p, char *lim, int exp)
{
	char	*s;

	close(p[0]);
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
	close(p[1]);
	exit(0);
}

int	here_doc(char *lim, int exp)
{
	int	p[2];
	int	id;

	pipe(p);
	if (lim && (lim[0] == '\'' || lim[0] == '\"'))
		exp = 0;
	id = fork();
	if (id == 0)
		utilhere_doc(p, lim, exp);
	close(p[1]);
	wait(0);
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
			t->i_f = here_doc(t->cmd[++i], 1);
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
	int	i;

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
