/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:04:25 by ajari             #+#    #+#             */
/*   Updated: 2023/03/13 19:16:50 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_new(char *s1, char *s2)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = s1;
	new->equals = 0;
	new->value = s2;
	new->next = NULL;
	return (new);
}

void	envadd_back(t_env **lst, t_env *new)
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

t_env	*getlstenv(char **ev)
{
	t_env *env;
	t_env *new;
	char **e;
	int i;

	env = 0;
	i = 0;
	e = 0;
	while (ev && ev[i])
	{
		e = ft_split(ev[i], '=');
		new = env_new(e[0], e[1]);
		if (new)
			new->equals = 1;
		envadd_back(&env, new);
		free(e[2]);
		free(e);
		i++;
	}
	return (env);
}
