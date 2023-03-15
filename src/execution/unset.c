/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:44:38 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/13 16:57:00 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_delete_key(t_env *env, char *key)
{
	t_env	*delete;

	while (env->next)
	{
		if (!ft_strcmp(env->next->key, key))
		{
			delete = env;
			env->next = env->next->next;
			free(delete->key);
			free(delete->value);
			free(delete);
			return ;
		}
		env = env->next;
	}
}

void	unset()
{
	int		i;
	t_env	*env;
	t_env	*delete;
	
	i = 0;
	while (data->cmdsp[i])
	{
		if (!ft_strcmp(data->env->key, data->cmdsp[i]))
		{
			delete = data->env;
			data->env = data->env->next;
			free(delete->key);
			free(delete->value);
			free(delete);
		}
		else
			ft_delete_key(data->env, data->cmdsp[i]);
		i++;
	}
}