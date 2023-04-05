/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:44:19 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/05 00:44:28 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

char	**ft_env(t_env *env)
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
		if (env->equals == 1)
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
	p = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
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
	if (comand[0] == '/' && access(comand, F_OK) == 0)
		return (comand);
	if (comand[0] == '.')
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

char	*srch_path(void)
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

void	ft_child(t_list *list, char *comand, char *path)
{
	if (!builtins(list, 1))
	{
		if (list->cmdsp && list->cmdsp[0][0] == '/')
			execve(list->cmdsp[0], list->cmdsp, ft_env(g_v->env));
		path = srch_path();
		if ((list->cmdsp && list->cmdsp[0] && !list->cmdsp[0][0]) || !path)
		{
			error(" : command not found", list->cmdsp[0]);
			exit_status(127, 1);
		}
		comand = cmd_access(a_split(path, ':'), list->cmdsp[0]);
		if (!comand)
		{
			error(" : command not found", list->cmdsp[0]);
			exit_status(127, 1);
		}
		if (access(comand, X_OK))
			prror_cmd(126);
		execve(comand, list->cmdsp, ft_env(g_v->env));
		prror_cmd(127);
	}
}
