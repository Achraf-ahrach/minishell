/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 07:24:13 by ajari             #+#    #+#             */
/*   Updated: 2023/03/15 17:33:12 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			while (s[i] != c)
				i++;
		}
		if (!s[i])
			return (error(c, "do not forget to close quotes"));
		i++;
	}
	return (1);
}

static int	check_file(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '<' && s[i + 1] == '<')
		{
			while (ft_isspace(s[++i]))
				;
			if (s[i] == '<' && s[i] == '>')
				return (error(c, ""))
		}
		i++;
	}
}

int	check_in(char *s)
{
	int len;
	int i;
	char c;

	i = 0;
	len = ft_strlen(s) - 1;
	while (ft_isspace(s[len]))
		len--;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '|' || s[len] == '|' || s[len] == '>' || s[len] == '<')
	{
		(s[i] == '|') && (c = '|');
		(s[len] == '|') && (c = '|');
		(s[len] == '<') && (c = '<');
		(s[len] == '>') && (c = '>');
		return (error(c, "syntax error near unexpected token"));
	}
	return (check_quote(s));
}