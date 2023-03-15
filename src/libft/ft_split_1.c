/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 07:37:12 by ajari             #+#    #+#             */
/*   Updated: 2023/03/15 17:10:30 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_c(char const *s, char c)
{
	size_t	i;
	size_t	result;
	char	v;

	i = 0;
	result = 0;
	while (s && s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			v = s[i];
			i++;
			while (s[i] != v)
				i++;
		}
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
void	util_split1(const char *s, char c, size_t *start, size_t *end)
{
	char	v;

	*start = *end;
	while (s[*start] == c && s[*start])
		*start += 1;
	*end = *start;
	while (s[*end] != c && s[*end])
	{
		if (s[*end] == '\'' || s[*end] == '"')
		{
			v = s[*end];
			*end += 1;
			while (s[*end] != v)
				*end += 1;
		}
		*end += 1;
	}
}

char	**ft_split1(char const *s, char c)
{
	size_t	i;
	char	**result;
	size_t	start;
	size_t	end;

	i = 0;
	end = 0;
	result = 0;
	if (s)
	{
		result = ft_calloc(count_c(s, c) + 1, sizeof(char *));
		while (result && i < count_c(s, c))
		{
			util_split1(s, c, &start, &end);
			result[i++] = ft_substr(s, start, end - start);
			if (!result[i - 1])
				return (ft_free(result, i - 1));
		}
	}
	return (result);
}
