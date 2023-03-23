/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:44:38 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/21 17:35:54 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

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
	t_env	*delete;
	
	i = 0;
	while (g_v->cmdsp[i])
	{
		if (!ft_strcmp(g_v->env->key, g_v->cmdsp[i]))
		{
			delete = g_v->env;
			g_v->env = g_v->env->next;
			free(delete->key);
			free(delete->value);
			free(delete);
		}
		else
			ft_delete_key(g_v->env, g_v->cmdsp[i]);
		i++;
	}
}