/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rm_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:57:37 by ajari             #+#    #+#             */
/*   Updated: 2023/03/17 08:47:24 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

static void	rm_quote_uti(char *s, int *i, char c, int this)
{
	while (this == -1 && s[*i + 1] != c && s[*i])
	{
		if (s[*i + 1] == '|')
			s[*i] = 1;
		else if (s[*i + 1] == '>')
			s[*i] = 2;
		else if (s[*i + 1] == '<')
			s[*i] = 3;
		else if (s[*i + 1] == ' ')
			s[*i] = -1;
		else
			s[*i] = s[*i + 1];
		*i += 1;
	}
	while (this != -1 && s[this])
	{
		s[this] = s[this + 2];
		this ++;
	}
}

int	rm_quote(t_env *env, char *s, int i, char c)
{
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i];
			s[i] = 1;
			rm_quote_uti(s, &i, c, -1);
			if (!s[i])
			{
				free(s);
				return (error(c, "unclose quote"));
			}
			rm_quote_uti(s, &i, c, i);
		}
		else
			i++;
	}
	fill_cmds(s, env);
	free(s);
	return (1);
}
