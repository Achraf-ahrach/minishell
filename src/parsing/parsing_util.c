/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2023/04/01 22:14:25 by ajari             #+#    #+#             */
/*   Updated: 2023/04/01 23:17:40 by ajari            ###   ########.fr       */
=======
/*   Created: 2023/03/03 20:43:23 by ajari             #+#    #+#             */
/*   Updated: 2023/04/01 23:44:35 by aahrach          ###   ########.fr       */
>>>>>>> ac890e2c668fdbc15ecf3c7fb7d63d5f324bf829
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

	fd = -2;
	name = expend(ft_strdup(name), 0, 1, &fd);
	if (fd == -1)
		return (fd);
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
	fd = 1;
	name = expend(ft_strdup(name), 0, 1, &fd);
	if (fd == -1)
		return (*stat = 0, fd);
	if (!access(name, F_OK))
	{
		if (access(name, W_OK) == -1)
			return (error("permission denied", name), *stat = 0, -1);
	}
=======
	if (access(name, W_OK) == -1 && access(name, W_OK) == -1)
		return (error("permission denied", name), *stat = 0, -1);
>>>>>>> ac890e2c668fdbc15ecf3c7fb7d63d5f324bf829
	if (trunc)
		fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
		fd = open(name, O_CREAT | O_APPEND | O_WRONLY, 0777);
	return (fd);
}

int	len_name(char *s, int *j)
{
	int	i;

	i = 0;
	while (s[i] && (!ft_isspace(s[i])))
		i++;
	*j += i + 1;
	return (i);
}
