/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:54:50 by ajari             #+#    #+#             */
/*   Updated: 2023/04/04 16:07:20 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	nb(char **dup, char *s, int *fd)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (s && s[i])
	{
		if ((!i && !ft_isspace(s[i])) || (ft_isspace(s[i]) && !ft_isspace(s[i
					+ 1]) && s[i + 1]))
			result++;
		i++;
	}
	if (result > 1 && *fd)
		return (*fd = -1, 0);
	add_chars(dup, s, 0);
	return (1);
}

void	search_replace(int *fd, char *s, char **dup, int *i)
{
	char	*d;
	t_env	*env;

	env = g_v->env;
	d = ft_substr(s + 1, 0, len_name(s + 1, i));
	if (!ft_strcmp("?", d))
		add_chars(dup, ft_itoa(g_v->var->exit_status), 1);
	else
	{
		while (env)
		{
			if (!ft_strcmp(env->key, d) && nb(dup, env->value, fd))
				break ;
			env = env->next;
		}
	}
	(!env && !*fd) && (add_chars(dup, "\"\"", 0));
	if (!env && *fd)
	{
		*fd = -1;
		error("ambiguous redirect", d);
	}
	free(d);
}

void	no_expend(char *s, char **dup, char c, int *i)
{
	char	*t;
	int		j;

	j = 0;
	add_char(dup, s[*i]);
	if (s[*i] == '\'')
	{
		while (1)
		{
			*i += 1;
			add_char(dup, s[*i]);
			if (s[*i] == c)
				break ;
		}
		*i += 1;
		return ;
	}
	t = ft_substr(s + *i + 1, 0, ft_index(s + *i + 1, c));
	*dup = ft_strjoin(*dup, expend(t, 0, 1, &j));
	add_char(dup, c);
	*i += ft_index(s + *i + 1, c) + 2;
}

void	squiplim(char **dup, char *s, int *i)
{
	char	c;

	c = s[*i];
	while (ft_isspace(s[*i]) || s[*i] == c)
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

char	*expend(char *s, int i, int exp, int *fd)
{
	char	*dup;

	dup = NULL;
	if (!exp)
		return (s);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			no_expend(s, &dup, s[i], &i);
		else if (!ft_strncmp(&s[i], ">", 1) || !ft_strncmp(&s[i], "<", 1))
			squiplim(&dup, s, &i);
		else if (s[i] == '$' && ft_isdigit(s[i + 1]))
			i += 2;
		else if (s[i] == '$' && s[i + 1] == '$' && add_chars(&dup, "\"\"", 0))
			i += 2;
		else if (s[i] == '$' && (s[i + 1] == '\'' || s[i + 1] == '\"'))
			i++;
		else if (s[i] == '$' && !ft_isspace(s[i + 1]) && s[i + 1])
			search_replace(fd, &s[i], &dup, &i);
		else
			add_char(&dup, s[i++]);
	}
	return (free(s), dup);
}
