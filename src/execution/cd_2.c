/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:14:38 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/08 15:37:35 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	cd_oldpwd(t_list *list, t_env *env, int is_childe)
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
	ft_error("minishell: ", list->cmdsp[0], ": OLDPWD not set", 1);
	exit_status(1, is_childe);
}

void	cd_home(t_list *list, t_env *env, int is_childe)
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
	ft_error("minishell: ", list->cmdsp[0], ": HOME not set", 1);
	exit_status(1, is_childe);
}
