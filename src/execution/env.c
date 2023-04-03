/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:14:08 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/02 00:52:40 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

char	*get_env(t_env *env)
{
	char	*key;
	char	*value;
	char	*p;
	char	*s;

	key = ft_strdup(env->key);
	value = ft_strdup(env->value);
	s = strjoin_a(key, "=");
	p = ft_strjoin(s, value);
	return (p);
}

char	*strjoin_a(char const *s1, char const *s2)
{
	char	*p;
	int		k;
	int		i;
	int		j;
	int		c;

	c = 0;
	k = 0;
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	p = malloc((i + j + 1) * sizeof(char));
	if (p == 0)
		return (NULL);
	while (k < i)
	{
		p[k] = s1[k];
		k++;
	}
	while (k < i + j)
		p[k++] = s2[c++];
	p[k] = '\0';
	return (p);
}

void	env(t_env *env)
{
	while (env)
	{
		if (env->equals == 1)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
