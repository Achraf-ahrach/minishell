/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 07:24:13 by ajari             #+#    #+#             */
/*   Updated: 2023/03/15 08:54:34 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *s)
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
}

int	chck_pipe(char *s)
{
	int		len;
	int		i;
	char	c;

	len = ft_strlen(s) - 1;
	while ()
		if (s[0] == '|' || s[len] == '|' || s[len] == '>' || s[len] == '<')
		{
			(s[0] == '|') && (c = '|');
			(s[ft_strlen(s) - 1] == '|') && (c = '|');
			(s[ft_strlen(s) - 1] == '<') && (c = '<');
			(s[ft_strlen(s) - 1] == '>') && (c = '>');
			exit(error(c, "syntax error near unexpected token"));
		}
	return (1);
}
