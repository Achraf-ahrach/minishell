/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_0util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:43:23 by ajari             #+#    #+#             */
/*   Updated: 2023/03/15 10:35:47 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error(char c, char *str_er)
{
	print(c, 31, str_er);
	return (0);
}

int	open_fd(char **error, char *name, int mode)
{
	int	fd;

	fd = open(name, mode, 777);
	if (fd == -1)
		*error = strerror(errno);
	return(fd);
}

void	print(char c, int color, char *str)
{
	(void)c;
	if (color == 31)
		printf(RED);
	else if (color == 32)
		printf(GREEN);
	else if (color == 33)
		printf(WELLOW);
	else if (color == 34)
		printf(BLUE);
	else
		printf(AS_DEFAULT);
	printf("%s%c\n", str, c);
}
