/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:44:38 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/04 13:26:05 by aahrach          ###   ########.fr       */
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
			delete = env->next;
			env->next = env->next->next;
			free(delete->key);
			free(delete->value);
			free(delete);
			return ;
		}
		env = env->next;
	}
}

void	unset(t_list *list)
{
	int		i;
	t_env	*env;
	
	i = 0;
	if (!list->env)
		return ;
	while (list->cmdsp[i])
	{
		env = list->env;
			ft_delete_key(env, list->cmdsp[i]);
		i++;
	}
}