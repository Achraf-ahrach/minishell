/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_addsp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:59:02 by ajari             #+#    #+#             */
/*   Updated: 2023/04/05 15:09:31 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	add_arg(char *s, int *i, char ***cmd)
{
	char	*str;

	str = NULL;
	while (ft_isspace(s[*i]))
		*i += 1;
	if (s[*i] != '<' && s[*i] != '>')
	{
		while (!ft_isspace(s[*i]) && s[*i])
		{
			add_char(&str, s[*i]);
			*i += 1;
		}
		add_str(cmd, str);
	}
}

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
	free(s);
	return (dup);
}
