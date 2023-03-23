/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:44:19 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/21 18:47:07 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

char	*ft_strjoin_a(char const *s1, char const *s2)
{
	char	*p;
	int		k;
	int		i;
	int		j;
	int		c;

	c = 0;
	k = 0;
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	p = malloc((i + j + 1) * sizeof(char));
	if (p == 0)
		return (NULL);
	while (k < i)
	{
		p[k] = s1[k];
		k++;
	}
	while (k < i + j)
		p[k++] = s2[c++];
	p[k] = '\0';
	return (p);
}

char	*get_env(t_env *env)
{
	char	*key;
	char	*value;
	char	*p;
	char	*s;

	key = ft_strdup(env->key);
	value = ft_strdup(env->value);
	s = ft_strjoin_a(key, "=");
	p = ft_strjoin(s, value);
	return (p);
}

char	**ft_env(t_env	*env)
{
	t_env	*v;
	char	**p;
	int		i;

	i = 0;
	v = env;
	while (v)
	{
		if (v->equals == 1)
			i++;
		v = v->next;
	}
	p = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (env)
	{
		if(env->equals == 1)
		{
			p[i] = get_env(env);
			i++;
		}
		env = env->next;
	}
	p[i] = NULL;
	return (p);
}

char	*join_cmd(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	p = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (p == 0)
		return (NULL);
	while (*s1)
		p[i++] = *s1++;
	p[i++] = '/';
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}

char	*cmd_access(char **p, char *comand)
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
		path = join_cmd(p[j], comand);
		i = access(path, F_OK);
		if (i == -1)
			free(path);
		j++;
	}
	if (i == 0)
		return (path);
	return (NULL);
}

char	*srch_path()
{
	t_env	*env;

	env = g_v->env;
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	ft_child(t_list *list, int *pp)
{
	char	**p;
	char	*comand;
	char	*path;

	if (!builtins(1))
	{
		path = srch_path();
		if (!path)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putstr_fd(list->cmdsp[0], 2);
			exit_status (127);
		}
		p = ft_split(path, ':');
		comand = cmd_access(p, g_v->cmdsp[0]);
		if (!comand)
		{
			ft_putstr_fd(list->cmdsp[0], 2);
			ft_putstr_fd("minishell: command not found: ", 2);
			exit_status (127);
		}
		if (access(comand, X_OK))
		{
			perror("Error:");
			exit_status (126);
		}
		execve(comand, list->cmdsp, ft_env(g_v->env));
		perror("Error: ");
		exit_status (127);
	}
}