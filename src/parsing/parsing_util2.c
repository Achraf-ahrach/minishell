/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:59:40 by ajari             #+#    #+#             */
/*   Updated: 2023/04/06 16:28:07 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	expend_util(char **dup, char *s, char c, int *i)
{
	int	m;

	m = 0;
	while (s[*i] != c)
	{
		if (s[*i] == '$' && ft_isdigit(s[*i + 1]))
			*i += 2;
		else if (s[*i] == '$' && s[*i + 1] == '$' && add_chars(dup, "\"\"", 0))
			*i += 2;
		else if (s[*i] == '$' && (s[*i + 1] == '\'' || s[*i + 1] == '\"'))
			i++;
		else if (s[*i] == '$' && !ft_isspace(s[*i + 1]) && s[*i + 1])
			search_replace(&m, &s[*i], dup, i);
		else
		{
			add_char(dup, s[*i]);
			*i += 1;
		}
	}
	add_char(dup, s[*i]);
}
