/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:08:09 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/15 19:20:09 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	cd()
{
	int		len;
	t_env	*env;

	env = data->env;
	if (!data->cmdsp[1])
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
	else if (!ft_strcmp(data->cmdsp[1], "-"))
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
	}
	else if (chdir(data->cmdsp[1]))
		printf("minishell: %s: %s: No such file or directory\n", data->cmdsp[0], data->cmdsp[1]);
}
