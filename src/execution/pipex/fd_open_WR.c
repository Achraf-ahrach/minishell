/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_open_WR.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:54:10 by aahrach           #+#    #+#             */
/*   Updated: 2023/01/04 16:23:25 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	fd_open_wr(char **av)
{
	char	*str;
	char	*s;
	int		fd;
	int		j;

	j = 1;
	fd = open(av[1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	while (j != 0)
	{
		str = get_next_line(0);
		s = ft_join(av[2]);
		j = ft_memcmp(str, s);
		if (j == 1)
			write(fd, str, ft_strlen(str));
		free(str);
		free(s);
	}
	close(fd);
	fd = open(av[1], O_RDWR);
	return (fd);
}
