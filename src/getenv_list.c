/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:04:25 by ajari             #+#    #+#             */
/*   Updated: 2023/03/09 22:28:59 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*env_new(char *s1, char *s2)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = s1;
	new->value = s2;
	new->next = NULL;
	return (new);
}

static void	envadd_back(t_env **lst, t_env *new)
{
	t_env	*t;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		t = *lst;
		while (t->next)
			t = t->next;
		t->next = new;
	}
}

static void	swap(t_env *t, t_env *t1)
{
	char	*tmp;

	tmp = t->key;
	t->key = t1->key;
	t1->key = tmp;
	tmp = t->value;
	t->value = t1->value;
	t1->value = tmp;
}

static void	sort_env(t_env **env)
{
	t_env	*t;
	t_env	*t1;

	t = *env;
	while (env && t)
	{
		t1 = t;
		while (t1->next)
		{
			if (ft_strcmp(t->key, t1->next->key) > 0)
			{
				swap(t, t1->next);
			}
			t1 = t1->next;
		}
		t = t->next;
	}
}
t_env	*getlstenv(char **ev)
{
	(void)ev;
	t_env *env;
	char **e;
	int i;

	env = 0;
	i = 0;
	e = 0;

	while (ev && ev[i])
	{
		e = ft_split(ev[i], '=');
		envadd_back(&env, env_new(e[0], e[1]));
		free(e[2]);
		free(e);
		i++;
	}
	sort_env(&env);
	return (env);
}