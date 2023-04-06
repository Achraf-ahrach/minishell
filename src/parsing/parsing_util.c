/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:14:25 by ajari             #+#    #+#             */
/*   Updated: 2023/04/06 10:32:02 by ajari            ###   ########.fr       */
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

int	infd(char **name, int *stat)
{
	int	fd;

	fd = 1;
	*name = rm_quote(expend(*name, 0, 1, &fd));
	if (fd == -1)
		return (*stat = -1, fd);
	if (access(*name, F_OK) == -1)
		return (error("No such file or directory", *name), *stat = 0, -1);
	if (access(*name, R_OK) == -1)
		return (error("Permission denied", *name), *stat = 0, -1);
	fd = open(*name, O_RDONLY, 777);
	return (fd);
}

int	outfd(char **name, int trunc, int *stat)
{
	int	fd;

	fd = 1;
	*name = rm_quote(expend(*name, 0, 1, &fd));
	if (fd == -1)
		return (*stat = 0, fd);
	if (!access(*name, F_OK) && access(*name, W_OK) == -1)
		return (error("Permission denied", *name), *stat = 0, -1);
	if (trunc)
		fd = open(*name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
		fd = open(*name, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (fd == -1)
		return (error("No such file or directory", *name), *stat = 0, -1);
	return (fd);
}

int	len_name(char *s, int *j)
{
	int	i;

	i = 0;
	if (s[i] == '?')
	{
		*j += i + 2;
		return (1);
	}
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	*j += i + 1;
	return (i);
}

void	count_heredoc(t_list *t)
{
	int count;
	int i;

	count = 0;
	while (t)
	{
		i = 0;
		while (t->cmd && t->cmd[i])
		{
			if (!ft_strcmp(t->cmd[i], "<<"))
				count++;
			i++;
		}
		t = t->next;
	}
	if (count > 16)
		exit(error("maximum here-document count exceeded", "") + 2);
}