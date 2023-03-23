/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:08:02 by ajari             #+#    #+#             */
/*   Updated: 2023/03/17 09:43:41 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_c(char *s, char c)
{
	size_t	i;
	size_t	result;

	i = 0;
	result = 0;
	while (s && s[i])
	{
		if ((i == 0 && s[i] != c) || (s[i] == c && s[i + 1] != c && s[i + 1]))
			result++;
		i++;
	}
	return (result);
}

static char	**ft_free(char **result, int i)
{
	while (i)
		free(result[--i]);
	free(result);
	return (0);
}

void	utils(char c, char *s, size_t *start, size_t *end)
{
	*start = *end;
	while (s[*start] == c && s[*start])
		*start += 1;
	*end = *start;
	while (s[*end] != c && s[*end])
		*end += 1;
}

void	str_chiffre(char *s, int i, char v, char *c)
{
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			v = s[i++];
			while (s[i] != v)
				i++;
		}
		else if (s[i] == *c)
			s[i] = -1;
		i++;
	}
	*c = -1;
}

char	**ft_split(char *s, char c, int chiffre)
{
	size_t	i;
	char	**result;
	size_t	start;
	size_t	end;

	i = 0;
	end = 0;
	result = 0;
	if (!s)
		return (NULL);
	if (chiffre)
		str_chiffre(s, 0, 0, &c);
	result = ft_calloc(count_c(s, c) + 1, sizeof(char *));
	while (result && i < count_c(s, c))
	{
		utils(c, s, &start, &end);
		result[i++] = ft_substr(s, start, end - start);
		if (!result[i - 1])
			return (ft_free(result, i - 1));
	}
	free(s);
	return (result);
}
