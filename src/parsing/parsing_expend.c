/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:54:50 by ajari             #+#    #+#             */
/*   Updated: 2023/03/26 14:52:56 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	len_name(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
			|| s[i] == '_'))
		i++;
	return (i);
}

void	search_replace(t_env *env, char *s, char **dup, int *i)
{
	char	*d;

	d = ft_substr(s, 0, len_name(s));
	while (env)
	{
		if (!ft_strcmp(env->key, d))
			addmany_chars(dup, env->value, 0);
		if (!ft_strcmp("?", d))
			addmany_chars(dup, ft_itoa(g_v->var->exit_status), 1);
		env = env->next;
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

char	*expend(char *s, int i, int exp)
{
	char	*dup;

	dup = NULL;
	if (!exp)
		return (s);
	while (s[i])
	{
		if (s[i] == '\'')
			no_expend(s, &dup, '\'', &i);
		else if (s[i] == '$')
			search_replace(g_v->env, &s[i + 1], &dup, &i);
		else
		{
			add_char(&dup, s[i]);
			i++;
		}
	}
	free(s);
	return (dup);
}