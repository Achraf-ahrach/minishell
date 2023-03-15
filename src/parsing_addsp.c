/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_addsp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:59:02 by ajari             #+#    #+#             */
/*   Updated: 2023/03/15 07:25:08 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strlen_spc(char *s, char c, int i, int j)
{
	int	count;

	count = 0;
	while (chck_pipe(s) && s[i])
	{
		j = 0;
		(s[i] == c && i && s[i - 1] != ' ') && (count += 1);
		while (s[i] == c)
		{
			i++;
			j++;
			count++;
		}
		if (j > 2)
			print(c, 31, "Error in ");
		(i && s[i - 1] == c && s[i] != ' ') && (count += 1);
		if (!s[i])
			break ;
		count++;
		i++;
	}
	return (count);
}

static void	util_addspc(char *s, char *dup, int *i, int *j)
{
	char	c;

	c = s[*i];
	if (*i && s[*i - 1] != ' ')
	{
		dup[*i + *j] = ' ';
		*j += 1;
	}
	while (s[*i] == c)
	{
		dup[*i + *j] = s[*i];
		*i += 1;
	}
	if (s[*i] != ' ')
	{
		dup[*i + *j] = ' ';
		*j += 1;
	}
}

char	*add_spc(char *s, int i, int j, char c)
{
	char	*dup;

	dup = malloc(sizeof(char) * ft_strlen_spc(s, c, 0, 0) + 1);
	if (!dup)
		return (dup);
	while (s[i])
	{
		if (s[i] == c)
			util_addspc(s, dup, &i, &j);
		else
		{
			dup[i + j] = s[i];
			i++;
		}
	}
	dup[i + j] = 0;
	free(s);
	if (c == '<')
		dup = add_spc(dup, 0, 0, '>');
	return (dup);
}
