/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:14:38 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/04 17:39:11 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	cd_oldpwd(t_env *env, int *eror)
{
	char	buffer[PATH_MAX];

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
	*eror = 2;
}

void	cd_home(t_env *env, int *eror)
{
	char	buffer[PATH_MAX];

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
	*eror = 2;
}
