/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:06:29 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/12 12:50:14 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	fd_open_wr(t_list *list)
{
	char	*str;
	char	*s;
	int		fd;
	int		j;

	j = 1;
	fd = open("walo", O_CREAT | O_RDWR | O_TRUNC, 0777);
	while (j != 0)
	{
		str = get_next_line(0);
		s = ft_join(list->limiter);
		j = ft_strcmp(str, s, ft_strlen(str));
		if (j == 1)
			write(fd, str, ft_strlen(str));
		free(str);
		free(s);
	}
	close(fd);
	fd = open("walo", O_RDWR);
	return (fd);
}

void	ft_child1_her(t_list *list, char *path, int *pi)
{
	char	**p;
	int		fd;
	char	**cm;
	char	*comand;

	p = ft_split(path, ':');
	if (p != NULL)
	{
		fd = fd_open_wr(list);
		comand = ft_check(p, list->cmd[0]);
		if (comand != NULL)
		{
			dup2(fd, 0);
			dup2(pi[1], 1);
			execve(comand, cm, list->envir);
		}
		perror(list->cmd[0]);
		ft_free(cm);
	}
	ft_free(p);
	exit(0);
}

void	ft_child2_her(t_list *list, char *path, int *pi)
{
	char	**p;
	char	*comand;
	char	**cm;
	int		fd;

	p = ft_split(path, ':');
	if (p != NULL)
	{
		comand = ft_check(p, list->cmd[0]);
		if (comand != NULL)
		{
			dup2(pi[0], 0);
			dup2(list->outfile, 1);
			execve(comand, cm, list->env);
		}
		ft_free(cm);
	}
	ft_free(p);
	perror(list->cmd[0]);
	exit (0);
}

char	*search_path(t_env *env, char *str, int len)
{
	int i = 0;

	while (env)
	{
		if (!ft_strcmp(env->key, "PATH="))
			return (env->value);
		i++;
		env = env->next;
	}
	return (NULL);
}

void	her_doc(t_list *list)
{
	int		i;
	int		pi[2];
	char	*path;

	i = 0;
	pipe(pi);
	if (fork() == 0)
	{
		path = search_path(list->env, "PATH=", 5);
		ft_child1_her(list, path, pi);
	}
	else
	{
		wait(NULL);
		close(pi[1]);
		unlink("walo");
		if (fork() == 0)
		{
			path = search_path(list->env, "PATH=", 5);
			ft_child2_her(list, path, pi);
		}
		wait(NULL);
		exit(0);
	}
}

int	check_n(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo(char **cmd)
{
	int i;
	int line;

	i = 1;
	line = 0;
	if (check_n(cmd[i]))
	{
		i++;
		line == 1;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
	}
	if (!line)
		printf("\n");
}

char	*pwd(int x)
{
	char buffer[FILENAME_MAX];

    if (getcwd(buffer, sizeof(buffer)))
	{
		if (x == 1)
			return ( buffer);
        printf("%s\n", buffer);
	}
    else
        printf("Error getting current working directory\n");
    return 0;
}

int	cut_pwd(char *pwd)
{
	int	len;

	len = ft_strlen(pwd);
	len--;
	while (len > 0)
	{
		if (pwd[len] == '/')
			return (len);
		len--;
	}
	return (0);
}

void	cd(char **cmd)
{
	int		i;
	char	*pwd_;
	int		len;
	char 	*cd;

	i = 1;
	if (!cmd[i] || !ft_strcmp(cmd[i], "."))
		return ;
	else if (!ft_strcmp(cmd[i], ".."))
	{
		pwd_ = pwd(1);
		len = cut_pwd(pwd_);
		if (len != 0)
		{
			cd = ft_substr(pwd_, 0, len);
			chdir(cd);
		}
	}
	else
	{
		if (chdir(cd) != 0)
			printf("minishell: %s: %s: No such file or directory\n", cmd[0], cd);
	}
}

// void	add_envir(t_list *list, char *key);
// {
// 	int		len_y;
// 	int		len_x;
// 	int		i;
// 	char	**env;
	
// 	len_y = 0;
// 	len_x = 0;
// 	i = 0;
// 	env = list->envir;
// 	while (env[len_y])
// 		len_y++;
// 	list->envir = malloc((len_y + 2) * sizeof(char *));
// 	//list->envir[len_y + 2] = NULL;
// 	while (env[i])
// 	{
// 		list->envir[i] = malloc(ft_strlen(env[i] + 1));
// 		ft_str
// 	}
// }

void	export_add(t_list *list, char *cmd, char *str)
{
	if (!ft_strcmp(str, "present"))
	{
		while (list->env)
		{
			if (!ft_strcmp(list->env->key, cmd))
			{
				list->env->value = cmd;
				return ;
			}
			list->env = list->env->next;
		}
	}
	else if (!ft_strcmp(str, "present"))
	{
		envadd_back(&list->env, cmd);
	}
}

char	*come_max(t_env *env)
{
	char	*max;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->index == 0)
			max = tmp->key;
		tmp = tmp->next;
	}
	while (env)
	{
		if (ft_strcmp(max, env->key) < 0)
		{
			if (env->index == 0)
				max = env->key;
		}
		env = env->next;
	}
}

void	sort_export(t_list *env)
{
	int		size;
	char	*max;
	t_env	*tmp;
	int		i;
	
	size = ft_lstlast(env);
	while (size > 0)
	{
		i = 0;
		tmp = env;
		max = come_max(env);
		while (i = 0)
		{
			if (ft_strcmp(max, tmp->key) == 0)
			{
				tmp->index = size;
				size--;
				i = 1;
			}
			tmp = tmp->next;
		}
	}
}

void	export(t_list *list)
{
	int		i;
	int		j;
	int 	size;
	t_env	*tmp;

	i = 1;
	if (!list->cmdsp[i])
	{
		sort_export(&list->env);
		size = ft_lstsize(list->env);
		while (size > 0)
		{
			tmp = list->env;
			while (tmp)
			{
				if (tmp->index == size)
				{
					printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
					size--;
					break ;
				}
				tmp = tmp->next;
			}
		}
	}
	else
	{
		tmp = list->env;
		while (list->cmdsp[i])
		{
			j = 0;
			while (tmp)
			{
				if (!ft_strcmp(tmp->key, list->cmd[i]))
				{
					export_add(tmp, list->cmdsp[i], "present");
					j = 1;
				}
				tmp = tmp->next;
			}
			if (j == 0)
				export_add(tmp, list->cmdsp[i], "absent");
			i++;
		}
	}
}

void	builtins(t_list *list)
{
	if (!ft_strcmp(list->cmdsp[0], "echo"))
		echo(list->cmd);
	else if (!ft_strcmp(list->cmdsp[0], "pwd"))
		pwd(0);
	else if (!ft_strcmp(list->cmdsp[0], "cd"))
		cd(&list->cmd);
	else if (!ft_strcmp(list->cmdsp[i], "export"))
		export(list);
}

void	execution(t_list *list)
{
	int	i;

	i = 0;
	list->env = getlstenv(list->envir);
	while (list)
	{
		builtins(list);
		// if (list[i].h_doc = 1)
		// 	her_doc(list);
	}
}

// int main()
// {
// 	t_list	*list;

// 	list = malloc(2 * sizeof(t_list));
// 	execution(list);
// }