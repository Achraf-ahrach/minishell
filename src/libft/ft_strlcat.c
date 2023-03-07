/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:21:00 by ajari             #+#    #+#             */
/*   Updated: 2023/01/22 18:58:39 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lend;
	size_t	lens;
	size_t	i;
	size_t	t;

	lend = 0;
	if (dst)
		lend = ft_strlen(dst);
	lens = ft_strlen(src);
	t = lend;
	i = 0;
	if (dstsize <= lend || dstsize == 0)
		return (lens + dstsize);
	while (src[i] && i < dstsize - lend - 1)
	{
		dst[t++] = src[i++];
	}
	dst[t] = 0;
	return (lend + lens);
}
