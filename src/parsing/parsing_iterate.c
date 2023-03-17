/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_iterate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:11:04 by ajari             #+#    #+#             */
/*   Updated: 2023/03/17 16:22:09 by ajari            ###   ########.fr       */
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
		*stat = -1;
		return (-1);
	}
	if (access(name, R_OK) == -1)
	{
		printf("minishell: %s :bermission denied\n", name);
		*stat = -1;
		return (-1);
	}
	fd = open(name, O_RDONLY, 777);
	return (fd);
}

int	outfd(char *name, int trunc, int *stat)
{
	int	fd;

	if (!access(name, F_OK))
	{
		if (access(name, W_OK) == -1)
		{
			printf("minishell: %s :bermission denied\n", name);
			*stat = -1;
			return (-1);
		}
	}
	if (trunc)
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 777);
	else
		fd = open(name, O_CREAT | O_WRONLY, 777);
	return (fd);
}

char	*here_doc(char *limeter)
{
	int	expend;
	char	*s;
	char	*str;

	str = NULL;
	if(str[0] == '\'' || str[0] == '\"')
		expend = 1;
	else
		expend = 0;
	while (1)
	{
		s = readline("\033[36;01mhere_doc>");
		if (!ft_strcmp(s, limeter))
			return (str);
		if(expend)
			str = ft_strjoin(str, ft_strjoin(s, ft_strdup("\n")));
	}
}

void	one_cmd(t_list *lst)
{
	int	i;

	i = 0;
	while (lst->cmd[i])
	{
		if (!ft_strcmp(lst->cmd[i], "<"))
			lst->infile = infd(lst->cmd[++i], &lst->stat);
		else if (!ft_strcmp(lst->cmd[i], "<<"))
			lst->h_d = here_doc(lst->cmd[++i]);
		else if (!ft_strcmp(lst->cmd[i], ">"))
			lst->outfile = outfd(lst->cmd[++i], 0, &lst->stat);
		else if (!ft_strcmp(lst->cmd[i], ">>"))
			lst->outfile = outfd(lst->cmd[++i], 1, &lst->stat);
		else
			add_str(&lst->cmdsp, lst->cmd[i++]);
	}
}

void	iterate_cmds(t_list *lst)
{
	int i;

	i = 0;

	while (lst)
	{
		one_cmd(lst);
		printf("stat :%d\n", lst->stat);
		lst = lst->next;
	}
}