/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:08:09 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/25 12:13:24 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	chang_pwd_oldpwd(char *oldpwd)
{
	char	buffer[PATH_MAX];
	t_env	*env;

	env = g_v->env;
	getcwd(buffer, sizeof(buffer));
	while (env)
	{
		if (!ft_strcmp(env->key, "PWD"))
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(buffer);
		}
		else if (!ft_strcmp(env->key, "OLDPWD"))
		{
			if (env->value)
				free(env->value);
			env->value = oldpwd;
			env->equals = 1;
		}
		env = env->next;
	}
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

void	cd(int is_child)
{
	t_env	*env;
	char	buffer[PATH_MAX];
	int		error;

	error = 0;
	env = g_v->env;
	if (!g_v->cmdsp[1] || !ft_strcmp(g_v->cmdsp[1], "~"))
	{
		while (env)
		{
			if (!ft_strcmp(env->key, "HOME"))
			{
				getcwd(buffer, sizeof(buffer));
				if (!chdir(env->value))
				{
					chang_pwd_oldpwd(ft_strdup(buffer));
					return ;
				}
			}
			env = env->next;
		}
		error = 1;
	}
	else if (!ft_strcmp(g_v->cmdsp[1], "-"))
	{
		while (env)
		{
			if (!ft_strcmp(env->key, "OLDPWD"))
			{
				getcwd(buffer, sizeof(buffer));
				if (!chdir(env->value))
				{
					chang_pwd_oldpwd(ft_strdup(buffer));
					printf("%s\n", env->value);
					return ;
				}
			}
			env = env->next;
		}
		error = 1;
	}
	else
	{
    	getcwd(buffer, sizeof(buffer));
		if (!chdir(g_v->cmdsp[1]))
			chang_pwd_oldpwd(ft_strdup(buffer));

		else
			error = 1;
	}
	if (error)
	{
		printf("minishell: %s: %s: No such file or directory\n", g_v->cmdsp[0], g_v->cmdsp[1]);
		exit_status(1);
	}
}
