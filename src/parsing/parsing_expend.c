/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:54:50 by ajari             #+#    #+#             */
/*   Updated: 2023/03/31 23:18:56 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	len_name(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '?')
		return (1);
	while (s[i] && ft_isalnum(s[i]) || s[i] == '_')
		i++;
	return (i);
}

void	search_replace(t_env *env, char *s, char **dup, int *i)
{
	char	*d;

	d = ft_substr(s, 0, len_name(s));
	if (!ft_strcmp("?", d))
		add_chars(dup, ft_itoa(g_v->var->exit_status), 1);
	else
	{
		while (env)
		{
			if (!ft_strcmp(env->key, d))
				add_chars(dup, env->value, 0);
			env = env->next;
		}
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

void	squiplim(char **dup, char *s, int *i)
{
	(void)dup;
	while (ft_isspace(s[*i]) || s[*i] == '<')
	{
		add_char(dup, s[*i]);
		*i += 1;
	}
	while (!ft_isspace(s[*i]) && s[*i])
	{
		add_char(dup, s[*i]);
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
		else if (!ft_strncmp(&s[i], "<<", 2))
			squiplim(&dup, s, &i);
		else if (s[i] == '$' && ft_isdigit(s[i + 1]))
			i += 2;
		else if (s[i] == '$' && s[i + 1] == '$' && add_chars(&dup, "\"\"", 0))
			i += 2;
		else if (s[i] == '$' && (s[i + 1] == '\'' || s[i + 1] == '\"'))
			i++;
		else if (s[i] == '$' && s[i + 1] != ' ' && s[i + 1])
			search_replace(g_v->env, &s[i + 1], &dup, &i);
		else
			add_char(&dup, s[i++]);
	}
	return (free(s), dup);
}
