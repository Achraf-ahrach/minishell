/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:32:10 by aahrach           #+#    #+#             */
/*   Updated: 2023/01/03 19:33:12 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free_get(char *buf, char **p)
{
	free(*p);
	*p = NULL;
	free(buf);
	return (NULL);
}

char	*ft_read_get(int fd, char **p, char *buf)
{
	char	*new;
	int		len;
	int		i;

	new = NULL;
	len = 1;
	while (len > 0)
	{
		len = read(fd, buf, BUFFER_SIZE);
		if (len == -1)
			return (ft_free_get(buf, p));
		buf[len] = '\0';
		*p = ft_strjoin_get(*p, buf);
		i = check_line_get(*p);
		if (i != -1)
		{
			new = ft_substr_get(*p, 0, i, 0);
			*p = ft_substr_get(*p, i + 1, ft_strlen_get(*p), 1);
			free (buf);
			return (new);
		}
	}
	new = ft_substr_get(*p, 0, ft_strlen_get(*p), 0);
	ft_free_get(buf, p);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*p;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buf)
		return (NULL);
	return (ft_read_get(fd, &p, buf));
}
