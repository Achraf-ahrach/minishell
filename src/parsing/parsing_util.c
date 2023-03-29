/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:43:23 by ajari             #+#    #+#             */
/*   Updated: 2023/03/29 12:03:10 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	error(char *str_er, char *name)
{
	write(2, RED, ft_strlen(RED));
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(str_er, 2);
	return (0);
}

int	infd(char *name, int *stat)
{
	int	fd;

	if (access(name, F_OK) == -1)
		return (error(": no such file or directory\n", name), *stat = 0, -1);
	if (access(name, R_OK) == -1)
		return (error(": bermission denied\n", name), *stat = 0, -1);
	fd = open(name, O_RDONLY, 777);
	return (fd);
}

int	outfd(char *name, int trunc, int *stat)
{
	int	fd;

	if (access(name, W_OK) == 0 && access(name, W_OK) == -1)
		return (error(": permission denied\n", name), *stat = 0, -1);
	if (trunc)
		fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
		fd = open(name, O_CREAT | O_WRONLY, 0777);
	return (fd);
}
