/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:12:07 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/15 16:14:30 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize_env(t_env *env)
{
	int size;

	size = 0;
	while (env)
	{
		env = env->next;
		size++;
	}
	return (size);
}

char	*cat_equals(char *str, int x)
{
	int		i;
	int		len;
	char	*p;

	i = 0;
	len = 0;
	while (str[i] && str[i] != '=')
		len++;
	p = malloc(len + 2);
	i = 0;
	while(str[i])
	{
		p[i] = str[i];
		i++;
		if (str[i] == '=' && x == 1)
		{
			p[i] = str[i];
			p[i + 1] = '\0';
			return (p);
		}
		else if (str[i] == '=' && x == 0)
		{
			p[i] = '\0';
			return (p);
		}
	}
	if (p)
		free(p);
	return (NULL);
}

void	export_add(t_env *env, char *key, char *str)
{
	char	*e;
	t_env	*new;

	if (!ft_strcmp(str, "present"))
	{
		if (env->value)
			free(env->value);
		env->key = ft_strrchr(key, '=') + 1;
		env->equals = 1;
	}
	else if (!ft_strcmp(str, "absent"))
	{
		e = cat_equals(key, 0);
		if (e)
		{
			new = env_new(e, ft_strrchr(key, '=') + 1);
			new->equals = 1;
			envadd_back(&data->env, new);
			free(e);
			return ;
		}
		new = env_new(key, NULL);
		envadd_back(&data->env, new);
	}
	else
	{
		e = ft_strjoin(env->value, key);
		if (env->value)
			free(env->value);
		env->value = e;
	}
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

void	sort_export(t_env *env)
{
	int		size;
	char	*max;
	t_env	*tmp;
	int		j;
	
	j = 1;
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


int	check_identifier(char *str)
{
	int	i;
	int	error;

	error = 0;
	i = 1;
	if (!ft_isalpha(str[0]))
		error = 1;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
			i++;
		else if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		else
			error = 1;
	}
	if (error == 1)
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier", 2);
		return (0);
	}
	return (1);
}

void	export_()
{
	t_env	*tmp;
	int		i;
	char	*p;
	char	*s;
	char	*l;

	i = 1;
	tmp = data->env;
	while (data->cmdsp[i])
	{
		if (check_identifier(data->cmdsp[i]))
		{
			while (tmp)
			{
				p = cat_equals(data->cmdsp[i], 0);
				if (p)
				{
					if (!ft_strcmp(tmp->key, p))
					{
						export_add(tmp, data->cmdsp[i], "present");
						free(p);
						return ;
					}
					l = ft_strdup("+");
					s = ft_strjoin(tmp->key, l);
					if (!ft_strcmp(tmp->key, s))
					{
						export_add(tmp, ft_strrchr(data->cmdsp[i], '=') + 1, "join");
						free(p);
						free(s);
					}
					free(p);
					free(s);
				}
				tmp = tmp->next;
			}
			export_add(tmp, data->cmdsp[i], "absent");
		}
		i++;
	}
}

void	export()
{
	int		i;
	int 	size;
	t_env	*tmp;

	i = 1;
	if (!data->cmdsp[i])
	{
		sort_export(data->env);
		size = ft_lstsize_env(data->env);
		while (size > 0)
		{
			tmp = data->env;
			while (tmp)
			{
				if (tmp->index == size && tmp->equals == 1)
				{
					printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
					size--;
					break ;
				}
				else if (tmp->index == size && tmp->equals == 0)
				{
					printf("declare -x %s\"%s\"\n", tmp->key, tmp->value);
					size--;
					break ;
				}
				tmp = tmp->next;
			}
		}
	}
	else
		export_();
}