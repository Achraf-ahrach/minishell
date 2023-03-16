/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:52:41 by aahrach           #+#    #+#             */
/*   Updated: 2023/01/04 17:49:38 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_memcmp(char *s1, char *s2)
{
	int	i;
	int	n;
	int	j;

	i = 0;
	n = ft_strlen(s1);
	j = ft_strlen(s2);
	if (n != j)
		return (1);
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_join(char *p)
{
	int		i;
	int		j;
	char	*s;

	j = 0;
	i = ft_strlen(p);
	s = malloc(i + 2 * sizeof(char));
	while (p[j])
	{
		s[j] = p[j];
		j++;
	}
	s[j++] = '\n';
	s[j] = '\0';
	return (s);
}

void	ft_child1_bon(char **av, char **env, int *pi, int i)
{
	char	**p;
	int		fd;
	char	**cm;
	char	*comand;

	if (i != -1)
	{
		p = ft_split(env[i] + 5, ':');
		if (p != NULL)
		{
			fd = fd_open_wr(av);
			cm = ft_split(av[3], ' ');
			comand = ft_check(p, cm[0]);
			if (comand != NULL)
			{
				dup2(fd, 0);
				dup2(pi[1], 1);
				execve(comand, cm, env);
			}
			ft_free(cm);
		}
		ft_free(p);
	}
	perror("error");
	exit(0);
}

void	ft_child2_bon(char **av, char **env, int *pi, int i)
{
	char	**p;
	char	*comand;
	char	**cm;
	int		fd;

	if (i != -1)
	{
		p = ft_split(env[i] + 5, ':');
		if (p != NULL)
		{
			cm = ft_split(av[4], ' ');
			comand = ft_check(p, cm[0]);
			if (comand != NULL)
			{
				fd = open(av[5], O_CREAT | O_WRONLY | O_APPEND, 0777);
				dup2(pi[0], 0);
				dup2(fd, 1);
				execve(comand, cm, env);
			}
			ft_free(cm);
		}
		ft_free(p);
	}
	perror("error");
	exit (0);
}

void	her_doc(char **av, char **env)
{
	int	i;
	int	pi[2];

	i = 0;
	pipe(pi);
	if (fork() == 0)
	{
		i = ft_strnstr(env, "PATH=", 5);
		ft_child1_bon(av, env, pi, i);
	}
	else
	{
		wait(NULL);
		close(pi[1]);
		unlink(av[1]);
		if (fork() == 0)
		{
			i = ft_strnstr(env, "PATH=", 5);
			ft_child2_bon(av, env, pi, i);
		}
		wait(NULL);
		exit(0);
	}
}
