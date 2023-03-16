/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:32:58 by aahrach           #+#    #+#             */
/*   Updated: 2023/01/04 10:46:43 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_get(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr_get(char *s, int start, int len, int x)
{
	char	*p;
	int		i;

	if (start > len)
		return (NULL);
	p = malloc((len - start + 2) * sizeof(char));
	if (!p)
	{
		free(s);
		return (NULL);
	}
	i = 0;
	while (start <= len)
		p[i++] = s[start++];
	if (x == 1)
		free(s);
	p[i] = '\0';
	if (p[0] == '\0')
	{
		free(p);
		return (NULL);
	}
	return (p);
}

int	check_line_get(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoin_get(char *s1, char *s2)
{
	char	*p;
	int		i;

	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		*s1 = '\0';
	}
	p = malloc((ft_strlen_get(s1) + ft_strlen_get(s2) + 1) * sizeof(char));
	if (!p)
	{
		free (s1);
		return (NULL);
	}
	i = -1;
	while (s1[++i])
		p[i] = s1[i];
	while (*s2)
		p[i++] = *s2++;
	p[i] = '\0';
	free(s1);
	return (p);
}
