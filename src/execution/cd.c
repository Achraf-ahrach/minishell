/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:08:09 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/07 00:27:28 by aahrach          ###   ########.fr       */
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

int	ft_error(char *one, char *two, char *thre, int new_line)
{
	write(2, RED, ft_strlen(RED));
	ft_putstr_fd(one, 2);
	ft_putstr_fd(two, 2);
	if (new_line)
		ft_putendl_fd(thre, 2);
	else
		ft_putstr_fd(thre, 2);
	write(2, AS_DEFAULT, ft_strlen(AS_DEFAULT));
	return (0);
}

void	cd_(t_list *list, int is_childe)
{
	char	buffer[PATH_MAX];

	getcwd(buffer, sizeof(buffer));
	if (!chdir(list->cmdsp[1]))
		chang_pwd_oldpwd(ft_strdup(buffer));
	else
	{
		ft_error("minishell: ", list->cmdsp[0], ": ", 0);
		ft_error(list->cmdsp[1], ": ", "No such file or directory", 1);
		exit_status(1, is_childe);
	}
}

void	cd(t_list *list, int is_childe)
{
	t_env	*env;

	env = list->env;
	if (!list->cmdsp[1] || !ft_strcmp(list->cmdsp[1], "~"))
		cd_home(list, env, is_childe);
	else if (!ft_strcmp(list->cmdsp[1], "-"))
		cd_oldpwd(list, env, is_childe);
	else
		cd_(list, is_childe);
}
