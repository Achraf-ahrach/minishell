/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:44:19 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/07 11:21:33 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

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
	if (!comand)
		return (NULL);
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

void	access_slash(t_list *list)
{
	if (list->cmdsp && ft_strchr(list->cmd[0], '/'))
	{
		if (access(list->cmdsp[0], F_OK) != -1)
			execve(list->cmdsp[0], list->cmdsp, ft_env(g_v->env));
		error(" : No such file or directory", list->cmdsp[0]);
		exit_status(127, 1);
	}
}

void	ft_child(t_list *list, char *comand, char *path)
{
	if (list->cmdsp && !builtins(list, 1))
	{
		access_slash(list);
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
	exit (1);
}
