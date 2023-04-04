/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:53:20 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/04 19:53:49 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	export_add(t_list *list, char *key, char *value)
{
	t_env	*new;

	new = env_new(key, value);
	envadd_back(&list->env, new);
}

int	check_identifier(char *str, int is_childe, int i)
{
	int	error;

	error = 0;
	if (!ft_isalpha(str[0]))
		error = 1;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
			i++;
		else if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
			return (1);
		else
		{
			error = 1;
			break ;
		}
	}
	if (error == 1)
	{
		ft_error("minishell: export: '", str, "': not a valid identifier", 1);
		exit_status(1, is_childe);
		return (0);
	}
	return (1);
}

int	ft_lstsize_env(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		env = env->next;
		size++;
	}
	return (size);
}

void	sort_export(t_env *env, int j, int size)
{
	char	*max;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		tmp->index = 0;
		tmp = tmp->next;
	}
	size = ft_lstsize_env(env);
	while (j <= size)
	{
		tmp = env;
		max = come_max(env);
		while (1)
		{
			if (ft_strcmp(max, tmp->key) == 0)
			{
				tmp->index = j;
				j++;
				break ;
			}
			tmp = tmp->next;
		}
	}
}