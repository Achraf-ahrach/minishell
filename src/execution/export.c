/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:12:07 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/31 21:47:34 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

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

char	*cat_equals(char *str, int *x)
{
	int		i;
	int		len;
	char	*p;

	i = 0;
	(*x) = 0;
	len = 0;
	while (str[len] && str[len] != '=' && str[len] != '+')
		len++;
	p = malloc(len + 2);
	i = 0;
	while(str[i])
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

void	export_add(t_env *env, char *key, char *value, char *str)
{
	t_env	*new;

	(void)str;
	(void)env;
	// if (!ft_strcmp(str, "present"))
	// {
	// 	if (env->value)
	// 		free(env->value);
	// 	env->value = value;
	// 	env->equals = 1;
	// 	env->index = 0;
	// }
	new = env_new(key, value);
	printf("key = %s   value = %s\n", new->key, new->value);
	envadd_back(&g_v->env, new);
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


int	check_identifier(char *str, int is_childe)
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

int	wach_kayn(t_list *list, char *str)
{
	t_env *env;

	env = list->env;
	while (env)
	{
		if (!ft_strcmp(str, env->key))
			return (1);
		env = env->next;
	}
	return (0);
}

char	*join_plus(char const *s1, char const *s2)
{
	char	*p;
	int		k;
	int		i;
	int		j;
	int		c;

	k = 0;
	c = 0;
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	p = malloc((i + j + 1) * sizeof(char));
	if (p == 0)
		return (NULL);
	while (k++ < i)
		p[k] = s1[k];
	while (k < i + j)
	{
		p[k++] = s2[c++];
	}
	p[k] = '\0';
	return (p);
}

void	export_(t_list *list, int	is_childe)
{
	t_env	*tmp;
	int		i;
	int		x;
	char	*p;
	// char	*s;
	// char	*l;
	char	*v;

	i = 1;
	v = NULL;
	while (list->cmdsp[i])
	{
		tmp = list->env;
		if (check_identifier(list->cmdsp[i], is_childe)  && !wach_kayn(list, list->cmdsp[i]))
		{
			p = cat_equals(list->cmdsp[i], &x);
			if (p)
				v = ft_substr(list->cmdsp[i], len_equal(list->cmdsp[i]) + 1, ft_strlen(list->cmdsp[i]));
			else
				p = ft_strdup(list->cmdsp[i]);
			//printf("====>%s\n", p);
			if (wach_kayn(list, p))
			{
				while (tmp)
				{
					if (!ft_strcmp(tmp->key, p) && x)
					{
						printf("======>    join\n");
						// export_add(tmp, ft_strrchr(list->cmdsp[i], '=') + 1, v,"join");
						tmp->value = ft_strjoin(tmp->value, v);
						break ;
					}
					if (!ft_strcmp(tmp->key, p))
					{
						printf("present\n");
						if (!v)
							break ;
						free(tmp->value);
						tmp->value = v;
						break ;
					}
					tmp = tmp->next;
				}
			}
			else
			{
				printf("absent\n");
				printf("key = %s    value = %s\n", p, v);
				export_add(tmp, p, v, "absent");
			}
			free(p);
		}
		i++;
	}
}

void	export(t_list *list, int is_childe)
{
	int		i;
	int 	size;
	t_env	*tmp;
	char	e;

	i = 1;
	size = 0;
	if (!list->cmdsp[i])
	{
		sort_export(list->env);
		size = ft_lstsize_env(list->env);
		while (size > 0)
		{
			tmp = list->env;
			while (tmp)
			{
				if (tmp->index == size)
				{
					printf("dfgdg=> 111 \n");
					if (!tmp->equals)
						e = '\0';
					else
						e = '=';
					if (tmp->value && ft_strcmp(tmp->key, "_"))
						printf("declare -x %s%c\"%s\"\n", tmp->key, e ,tmp->value);
					else if (ft_strcmp(tmp->key, "_"))
						printf("declare -x %s%c\n", tmp->key, e);
					size--;
					break ;
				}
				tmp = tmp->next;
			}
		}
	}
	else
		export_(list, is_childe);
}