/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:14:08 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/27 14:09:15 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	env(t_env *env)
{
	while (env)
	{
		if (env->equals == 1)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}