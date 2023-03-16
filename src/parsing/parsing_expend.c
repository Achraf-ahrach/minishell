/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:54:50 by ajari             #+#    #+#             */
/*   Updated: 2023/03/16 13:18:28 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"

int	len_name(char *s)
{
	int	i;

	i = 0;
	while ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
		|| s[i] == '_')
		i++;
	return (i);
}

void	search_replace(t_env *env, char *s, char **dup, int *i)
{
	int		j;
	char	*d;

	j = 0;
	d = ft_substr(s, 0, len_name(s));
	while (env)
	{
		if (!ft_strcmp(env->key, d))
			while (env->value[j])
				add_char(dup, env->value[j++]);
		env = env->next;
	}
	if (!env)
	{
		add_char(dup, '"');
		add_char(dup, '"');
	}
	free(d);
	*i += len_name(s) + 1;
}

void	no_expend(char *s, char **dup, char c, int *i)
{
	while (1)
	{
		add_char(dup, s[*i]);
		if (s[*i] != c)
			break ;
		*i += 1;
	}
}

char	*expend(t_env *env, char *s, int i)
{
	char	*dup;

	dup = NULL;
	while (s[i])
	{
		if (s[i] == '\'')
			no_expend(s, &dup, '\'', &i);
		else if (s[i] == '$')
			search_replace(env, &s[i + 1], &dup, &i);
		else
		{
			add_char(&dup, s[i]);
			i++;
		}
	}
	return (dup);
}
