/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:43:44 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/08 15:37:26 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

char	**ft_env(t_env *env)
{
	t_env	*v;
	char	**p;
	int		i;

	i = 0;
	v = env;
	while (v)
	{
		if (v->equals == 1)
			i++;
		v = v->next;
	}
	p = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (env)
	{
		if (env->equals == 1)
		{
			p[i] = get_env(env);
			i++;
		}
		env = env->next;
	}
	p[i] = NULL;
	return (p);
}

static int	ft_check(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i++] != c)
		{
			if (s[i] == c || s[i] == '\0')
				j++;
		}
	}
	return (j);
}

static int	ft_hseb(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static void	*ft_free_all(char **p, int a)
{
	while (a >= 0)
	{
		free(p[a]);
		a--;
	}
	free(p);
	return (NULL);
}

char	**a_split(char const *s, char c)
{
	char	**p;
	int		a;
	int		j;

	a = 0;
	if (!s)
		return (NULL);
	j = ft_check(s, c);
	p = malloc((j + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	while (a < j)
	{
		while (*s == c && *s)
			s++;
		p[a] = ft_substr(s, 0, ft_hseb(s, c));
		if (!p[a])
			return (ft_free_all(p, a));
		while (*s != c && *s != '\0')
			s++;
		a++;
	}
	p[a] = NULL;
	return (p);
}
