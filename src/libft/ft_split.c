/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:08:02 by ajari             #+#    #+#             */
/*   Updated: 2022/10/26 10:26:36 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_c(char const *s, char c)
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

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**result;
	size_t	start;
	size_t	end;

	i = 0;
	start = 0;
	result = 0;
	if (s)
	{
		result = ft_calloc(count_c(s, c) + 1, sizeof(char *));
		while (result && i < count_c(s, c))
		{
			while (s[start] == c && s[start])
				start++;
			end = start;
			while (s[end] != c && s[end])
				end++;
			result[i++] = ft_substr(s, start, end - start);
			if (!result[i - 1])
				return (ft_free(result, i - 1));
			start = end;
		}
	}
	return (result);
}
