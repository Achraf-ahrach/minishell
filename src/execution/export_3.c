/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:06:04 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/05 11:27:46 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	wach_kayn(t_list *list, char *str)
{
	t_env	*env;

	env = list->env;
	while (env)
	{
		if (!ft_strcmp(str, env->key))
			return (1);
		env = env->next;
	}
	return (0);
}

char	*cat_equals(char *str, int *x, int i)
{
	int		len;
	char	*p;

	(*x) = 0;
	len = 0;
	while (str[len] && str[len] != '=' && str[len] != '+')
		len++;
	p = malloc(len + 2);
	i = 0;
	while (str[i])
	{
		p[i] = str[i];
		i++;
		if (str[i] == '=' || str[i] == '+')
		{
			p[i] = '\0';
			if (str[i] == '+')
				(*x) = 1;
			return (p);
		}
	}
	if (p)
		free(p);
	return (NULL);
}

char	*come_max(t_env *env)
{
	char	*max;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->index == 0)
			max = tmp->key;
		tmp = tmp->next;
	}
	while (env)
	{
		if (ft_strcmp(max, env->key) < 0)
		{
			if (env->index == 0)
				max = env->key;
		}
		env = env->next;
	}
	return (max);
}
