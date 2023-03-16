/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 08:38:29 by aahrach           #+#    #+#             */
/*   Updated: 2023/01/04 19:06:25 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_check(char **p, char *comand)
{
	int		i;
	int		j;
	char	*path;

	j = 0;
	i = -1;
	if (access(comand, F_OK) == 0)
		return (comand);
	while (i != 0 && p[j] != NULL)
	{
		path = ft_strjoin(p[j], comand);
		i = access(path, F_OK);
		if (i == -1)
			free(path);
		j++;
	}
	if (i == 0)
		return (path);
	return (NULL);
}

void	ft_child1(char **av, char **env, int *pi)
{
	char	**p;
	int		fd;
	int		i;
	char	**cm;

	i = ft_strnstr(env, "PATH=", 5);
	if (i != -1)
	{
		p = ft_split(env[i] + 5, ':');
		if (p != NULL)
		{
			cm = ft_split(av[2], ' ');
			if (ft_check(p, cm[0]) != NULL)
			{
				fd = open(av[1], O_RDONLY);
				dup2(pi[1], 1);
				dup2(fd, 0);
				execve(ft_check(p, cm[0]), cm, env);
			}
			ft_free(cm);
		}
		ft_free(p);
	}
	perror("error");
	exit (0);
}

void	ft_child2_bonus(char **av, char **env, int ac)
{
	char	**p;
	int		fd;
	int		i;
	char	**cm;

	i = ft_strnstr(env, "PATH=", 5);
	if (i != -1)
	{
		p = ft_split(env[i] + 5, ':');
		if (p != NULL)
		{
			cm = ft_split(av[ac - 2], ' ');
			if (ft_check(p, cm[0]) != NULL)
			{
				fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
				dup2(fd, 1);
				execve(ft_check(p, cm[0]), cm, env);
			}
			ft_free(cm);
		}
		ft_free(p);
	}
	perror("error");
	exit (0);
}

void	ft_childw(char *av, char **env, int *pi)
{
	char	**p;
	char	*comand;
	char	**cm;
	int		i;

	i = ft_strnstr(env, "PATH=", 5);
	if (i != -1)
	{
		p = ft_split(env[i] + 5, ':');
		if (p != NULL)
		{
			cm = ft_split(av, ' ');
			comand = ft_check(p, cm[0]);
			if (comand != NULL)
			{
				dup2(pi[1], 1);
				execve(comand, cm, env);
			}
			ft_free(cm);
		}
		ft_free(p);
	}
	perror("error");
	exit (0);
}

int	main(int ac, char **av, char **env)
{
	int	pi[2];
	int	i;

	i = 0;
	if (ft_strnstr(av, "here_doc", 9) == 1 && ac == 6)
		her_doc(av, env);
	pipe(pi);
	if (i == 0 && fork() == 0)
		ft_child1(av, env, pi);
	close(pi[1]);
	i += 3;
	dup2(pi[0], 0);
	while (i < ac - 2)
	{
		pipe(pi);
		if (fork() == 0)
			ft_childw(av[i], env, pi);
		close(pi[1]);
		dup2(pi[0], 0);
		i++;
		if (i == ac - 2 && fork() == 0)
			ft_child2_bonus(av, env, ac);
	}
}
