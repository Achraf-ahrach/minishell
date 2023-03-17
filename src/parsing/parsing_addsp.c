/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_addsp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:59:02 by ajari             #+#    #+#             */
/*   Updated: 2023/03/17 09:38:43 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

static void	addbetwen_quote(char **dup, char *s, int *i)
{
	char	v;

	v = s[*i];
	while (1)
	{
		add_char(dup, s[*i]);
		*i += 1;
		if (s[*i] == v)
			break ;
	}
	add_char(dup, s[*i]);
	*i += 1;
}

static void	util_addsp(char **dup, char *s, int *i)
{
	char	c;

	c = s[*i];
	if (*i && s[*i - 1] != ' ')
		add_char(dup, ' ');
	add_char(dup, c);
	*i += 1;
	if (s[*i] == c)
	{
		add_char(dup, c);
		*i += 1;
	}
	if (s[*i] != ' ')
		add_char(dup, ' ');
}

char	*add_spc(char *s, int i)
{
	char	*dup;

	dup = NULL;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			addbetwen_quote(&dup, s, &i);
		else if (s[i] == '<' || s[i] == '>')
			util_addsp(&dup, s, &i);
		else
		{
			add_char(&dup, s[i]);
			i++;
		}
	}
	return (dup);
}
