/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 15:01:11 by aahrach           #+#    #+#             */
/*   Updated: 2023/01/04 16:27:38 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strnstr(char **haystack, char *needle, int len)
{
	int	i;
	int	j;

	i = 0;
	while (haystack[i])
	{
		j = 0;
		if (haystack[i][j] == needle[j])
		{
			while (haystack[i][j] == needle[j])
				j++;
			if (j == len)
				return (i);
		}
		i++;
	}
	return (-1);
}

void	ft_free(char **p)
{
	int	i;

	i = 0;
	if (!p)
		return ;
	while (p[i] != NULL)
		free(p[i++]);
	free(p[i]);
	free(p);
}
