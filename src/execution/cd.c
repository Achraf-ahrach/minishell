/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:08:09 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/22 12:21:42 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

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

	env = g_v->env;
	if (!g_v->cmdsp[1])
	{
		while (env)
		{
			if (!ft_strcmp(env->key, "HOME"))
			{
				chdir(env->value);
				return ;
			}
			env = env->next;
		}
	}
	else if (!ft_strcmp(g_v->cmdsp[1], "-"))
	{
		while (env)
		{
			if (!ft_strcmp(env->key, "OLDPWD"))
			{
				if (!chdir(env->value))
				{
					printf("%s\n", env->value);
					return ;
				}
			}
			env = env->next;
		}
		printf("minishell: cd: OLDPWD not set");
		exit_status(1);
	}
	else if (chdir(g_v->cmdsp[1]))
	{
		printf("minishell: %s: %s: No such file or directory\n", g_v->cmdsp[0], g_v->cmdsp[1]);
		if (is_child)
			exit_status(1);
	}
}
