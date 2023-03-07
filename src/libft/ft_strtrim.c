/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:26:26 by ajari             #+#    #+#             */
/*   Updated: 2022/10/25 22:24:55 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_m1(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s)
		i++;
	return (i);
}

static int	ft_start(const char *s1, const char *set)
{
	int	i;
	int	j;

	i = 0;
	if (!set)
		return (-1);
	while (s1 && s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				break ;
			j++;
		}
		if (set && set[j] == 0)
		{
			i--;
			break ;
		}
		i++;
	}
	return (i);
}

static int	ft_end(const char *s1, const char *set, size_t len_s1)
{
	int	j;

	while (len_s1 > 0 && set)
	{
		len_s1--;
		j = 0;
		while (set[j])
		{
			if (s1[len_s1] == set[j])
				break ;
			j++;
		}
		if (set[j] == 0)
			break ;
	}
	return (len_s1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		size;
	int		start;
	int		end;
	char	*p;

	if (!s1)
		return (NULL);
	start = ft_start(s1, set);
	end = ft_end(s1, set, ft_strlen_m1(s1));
	size = end - start + 1;
	if (end <= start)
		return (ft_strdup(""));
	p = malloc(size);
	if (!p)
		return (NULL);
	i = 0;
	start++;
	while (i < size - 1 && s1)
	{
		p[i] = s1[start + i];
		i++;
	}
	p[i] = 0;
	return (p);
}
