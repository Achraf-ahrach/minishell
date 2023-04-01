/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:43:23 by ajari             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/01 18:19:31 by aahrach          ###   ########.fr       */
=======
/*   Updated: 2023/04/01 18:42:22 by ajari            ###   ########.fr       */
>>>>>>> d314fef6c656e3aacafe64e032cca0f4851112c9
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	error(char *str_er, char *name)
{
	write(2, RED, ft_strlen(RED));
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str_er, 2);
	write(2, AS_DEFAULT, ft_strlen(AS_DEFAULT));
	return (0);
}

int	infd(char *name, int *stat)
{
	int	fd;

	if (access(name, F_OK) == -1)
		return (error("no such file or directory", name), *stat = 0, -1);
	if (access(name, R_OK) == -1)
		return (error("bermission denied", name), *stat = 0, -1);
	fd = open(name, O_RDONLY, 777);
	return (fd);
}

int	outfd(char *name, int trunc, int *stat)
{
	int	fd;

<<<<<<< HEAD
	if (access(name, W_OK) == -1 && access(name, W_OK) == -1)
=======
	name = expend(name, 0, 1, 1);
	if (access(name, W_OK) == -1)
		return (error("no such file or directory", name), *stat = 0, 1);
	if (access(name, W_OK) == -1)
>>>>>>> d314fef6c656e3aacafe64e032cca0f4851112c9
		return (error("permission denied", name), *stat = 0, -1);
	if (trunc)
		fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
		fd = open(name, O_CREAT | O_APPEND | O_WRONLY, 0777);
	return (fd);
}
