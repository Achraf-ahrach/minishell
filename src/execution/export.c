/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:12:07 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/06 15:26:49 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	help(t_env *tmp, char *key, char *value, int x)
{
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key) && x)
		{
			tmp->value = ft_strjoin(tmp->value, value);
			tmp->equals = 1;
			break ;
		}
		if (!ft_strcmp(tmp->key, key))
		{
			if (!value)
				break ;
			free(tmp->value);
			tmp->value = value;
			tmp->equals = 1;
			break ;
		}
		tmp = tmp->next;
	}
}

int	export_help(t_list *list, char *value, int i, int is_childe)
{
	t_env	*tmp;
	char	*key;
	int		x;

	tmp = list->env;
	if (check_identifier(list->cmdsp[i], is_childe, 0)
		&& !wach_kayn(list, list->cmdsp[i]))
	{
		key = cat_equals(list->cmdsp[i], &x, 0);
		if (key)
			value = ft_substr(list->cmdsp[i], len_equal(list->cmdsp[i]) + 1,
					ft_strlen(list->cmdsp[i]));
		else
			key = ft_strdup(list->cmdsp[i]);
		if (wach_kayn(list, key))
			help(tmp, key, value, x);
		else
		{
			export_add(list, key, value);
			return (0);
		}
		free(key);
	}
	return (1);
}

void	export_(t_list *list, int is_childe)
{
	int		i;

	i = 1;
	while (list->cmdsp[i])
	{
		if (!export_help(list, NULL, i, is_childe))
			break ;
		i++;
	}
}

void	print_export(t_list *list, t_env *tmp, int size)
{
	char	e;

	if (g_v->env)
			printf("1 key = %s | eqoual = %d | value = %s\n", g_v->env->key, g_v->env->equals, g_v->env->value);
	size = ft_lstsize_env(list->env);
	while (size > 0)
	{
		tmp = list->env;
		while (tmp)
		{
			if (tmp->index == size)
			{
				if (!tmp->equals)
					e = '\0';
				else
					e = '=';
				if (tmp->value && ft_strcmp(tmp->key, "_"))
					printf("declare -x %s%c\"%s\"\n", tmp->key, e, tmp->value);
				else if (ft_strcmp(tmp->key, "_"))
					printf("declare -x %s%c\n", tmp->key, e);
				size--;
				break ;
			}
			tmp = tmp->next;
		}
	}
}

void	export(t_list *list, int is_childe)
{
	int		size;

	size = 0;
	if (!list->cmdsp[1])
	{
		sort_export(list->env, 1, 0);
		print_export(list, NULL, 0);
	}
	else
		export_(list, is_childe);
}
