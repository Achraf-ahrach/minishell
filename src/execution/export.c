/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:12:07 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/28 17:32:57 by aahrach          ###   ########.fr       */
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

char	*cat_equals(char *str, int x)
{
	int		i;
	int		len;
	char	*p;

	i = 0;
	len = 0;
	while (str[len] && str[len] != '=')
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

void	export_add(t_env *env, char *key, char *value,char *str)
{
	t_env	*new;
	char	*e;

	if (!ft_strcmp(str, "present"))
	{
		//printf("9bel => key = %s\nvalue = %s\n", env->key, env->value);
		if (env->value)
			free(env->value);
		env->value = value;
		printf("key = %s\nvalue = %s\n", env->key, env->value);
		env->equals = 1;
		env->index = 0;
	}
	else if (!ft_strcmp(str, "absent"))
	{
		e = cat_equals(key, 0);
		if (e)
		{
			new = env_new(e, value);
			new->equals = 1;
			envadd_back(&g_v->env, new);
			//free(e);
			//printf("key = (%s)\nvalue = (%s)\n", e, value);
			return ;
		}
		new = env_new(ft_strdup(key), NULL);
		new->equals = 0;
		new->index = 0;
		//printf("key = (%s)\nvalue = (%s)\n", ft_strdup(key), NULL);
		envadd_back(&g_v->env, new);
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
		else if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
			return (1);
		else
			error = 1;
	}
	if (error == 1)
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier", 2);
		exit_status(1, 0);
		return (0);
	}
	return (1);
}

int	wach_kayn(char *str)
{
	t_env *env;

	env = g_v->env;
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

void	export_()
{
	t_env	*tmp;
	int		i;
	char	*p;
	char	*s;
	char	*l;
	char	*v;

	i = 1;
	v = NULL;
	s = "pp";
	while (g_v->cmdsp[i])
	{
		tmp = g_v->env;
		if (check_identifier(g_v->cmdsp[i])  && !wach_kayn(g_v->cmdsp[i]))
		{
			p = cat_equals(g_v->cmdsp[i], 0);
			if (p)
				v = ft_substr(g_v->cmdsp[i], len_equal(g_v->cmdsp[i]) + 1, ft_strlen(g_v->cmdsp[i]));
			else
				p = ft_strdup(g_v->cmdsp[i]);
			if (wach_kayn(p))
			{
				l = ft_strdup("+");
				s = join_plus(g_v->cmdsp[i], l);
				while (tmp)
				{
					if (!ft_strcmp(tmp->key, s))
					{
						printf("======>    join\n");
						export_add(tmp, ft_strrchr(g_v->cmdsp[i], '=') + 1, v,"join");
						break ;
					}
					if (!ft_strcmp(tmp->key, p))
					{
						printf("=======>    presnt\n");
						export_add(tmp, g_v->cmdsp[i], v, "present");
						break ;
					}
					tmp = tmp->next;
				}
				free(l);
				free(s);
			}
			else
			{
				printf("makaynach (%s)\n", p);
				export_add(tmp, g_v->cmdsp[i], v, "absent");
			}
			free(p);
		}
		i++;
	}
}

void	export()
{
	int		i;
	int 	size;
	t_env	*tmp;
	char	e;

	i = 1;
	size = 0;
	if (!g_v->cmdsp[i])
	{
		sort_export(g_v->env);
		size = ft_lstsize_env(g_v->env);
		while (size > 0)
		{
			tmp = g_v->env;
			while (tmp)
			{
				if (tmp->index == size)
				{
					if (!tmp->equals)
						e = '\0';
					else
						e = '=';
					if (tmp->value)
						printf("declare -x %s%c\"%s\"\n", tmp->key, e ,tmp->value);
					else
						printf("declare -x %s%c\n", tmp->key, e);
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