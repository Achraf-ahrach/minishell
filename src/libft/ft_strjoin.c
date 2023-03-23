/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:30:07 by ajari             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/19 16:51:22 by aahrach          ###   ########.fr       */
=======
/*   Updated: 2023/03/17 15:15:39 by ajari            ###   ########.fr       */
>>>>>>> 5f7ab26248fa6b442e2eb9cb89d2fd85c7098ff3
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sub;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	ft_memset((void *)sub, '*', len);
	if (s1)
	{
		ft_strlcpy(sub, s1, len + 1);
		free((void *)s1);
		s1 = 0;
	}
	if (s2)
	{
		ft_strlcat(sub, s2, len + 1);
		free((void *)s2);
		s2 = 0;
	}
	return (sub);
}
