/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rm_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:57:37 by ajari             #+#    #+#             */
/*   Updated: 2023/04/06 14:09:02 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

static void	rm_quote_uti(char *s, int i)
{
	while (1)
	{
		s[i] = s[i + 2];
		if (!s[i])
			break ;
		i++;
	}
}

char	*rm_quote(char *s)
{
	char	c;
	int		i;

	i = 0;
	printf("ss:%s\n", s);
	while (s && s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i];
			while (s[i + 1] != c)
			{
				s[i] = s[i + 1];
				i++;
			}
			rm_quote_uti(s, i);
		}
		else
			i++;
	}
	printf("ss:%s\n", s);
	return (s);
}
