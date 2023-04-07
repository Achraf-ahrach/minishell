/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 07:24:13 by ajari             #+#    #+#             */
/*   Updated: 2023/04/07 10:01:47 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

static int	check_quote(char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			c = s[i++];
			while (s[i] != c && s[i])
				i++;
		}
		if (!s[i])
			return (exit_status(258, 0), error("do not forget to close quotes",
					""));
		i++;
	}
	return (1);
}

static int	check_file(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '<' || s[i] == '>' || s[i] == '|')
		{
			c = s[i++];
			(s[i] == c) && (i++);
			while (ft_isspace(s[i]))
				i++;
			if (((c == '<' || c == '>') && (s[i] == '<' || s[i] == '>'
						|| s[i] == '|')) || (c == '|' && s[i] == '>'))
				return (exit_status(258, 0),
					error("syntax error near unexpected token `<<'", ""));
		}
		else
			i++;
	}
	return (1);
}

static int	check_pipe(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '|')
		{
			while (ft_isspace(s[++i]))
				;
			if (s[i] == '|')
				return (exit_status(258, 0),
					error("Minishell: Error sequance of pipe", ""));
		}
		else
			i++;
	}
	return (1);
}

int	check_in(char *s)
{
	int	len;
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
	{
		if (s[i] == '\t')
			s[i] = ' ';
		i++;
	}
	len = ft_strlen(s) - 1;
	while (len && ft_isspace(s[len]))
		len--;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '|' || s[len] == '|' || s[len] == '>' || s[len] == '<')
		return (exit_status(258, 0), error("syntax error near unexpected token",
				""));
	return (check_quote(s) * check_file(s, 0) * check_pipe(s));
}
