/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getlstenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:46:19 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/26 13:47:29 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

t_env	*env_new(char *s1, char *s2)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = s1;
	new->index = 0;
	new->equals = 1;
	new->value = s2;
	new->next = NULL;
	return (new);
}

void	envadd_back(t_env **lst, t_env *new)
{
	t_env	*t;

	if (!new)
		return ;
	if (!*lst)
		lst = &new;
	else
	{
		t = *lst;
		while (t->next)
			t = t->next;
		t->next = new;
	}
}

int	len_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=')
		i++;
	return (i);
}


t_env	*getlstenv(char **ev)
{
	t_env	*env;
	char	*k;
	char	*v;
	int		i;

	i = 0;
	k = 0;
	env = 0;
	while (ev && ev[i])
	{
		k = ft_substr(ev[i], 0, len_equal(ev[i]));
		v = ft_substr(ev[i], len_equal(ev[i]) + 1, ft_strlen(ev[i]));
		envadd_back(&env, env_new(k, v));
		i++;
	}
	g_v->env = env;
	return (env);
}