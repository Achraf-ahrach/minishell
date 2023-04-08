/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:14:08 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/08 15:38:28 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	check_max_long(char *str, int x, long nb, long nbr)
{
	if (x == 1 && nb > nbr)
	{
		ft_error("minishell: exit: ", str, ": numeric argument required", 1);
		exit_status(255, 1);
	}
	else if (x == -1 && nb > nbr && ft_strncmp(str, "-9223372036854775808", 20))
	{
		ft_error("minishell: exit: ", str, ": numeric argument required", 1);
		exit_status(255, 1);
	}
}

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
