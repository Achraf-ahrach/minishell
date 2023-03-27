/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:43:23 by ajari             #+#    #+#             */
/*   Updated: 2023/03/25 11:30:47 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	add_str(char ***s, char *str)
{
	int		i;
	char	**m;

	i = 0;
	while (*s && (*s)[i])
		i++;
	m = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (*s && (*s)[i])
	{
		m[i] = (*s)[i];
		i++;
	}
	m[i++] = str;
	m[i] = NULL;
	if (*s)
		free(*s);
	*s = m;
}

void	add_char(char **s, char c)
{
	char	*add;
	int		len;

	len = ft_strlen(*s);
	add = malloc(len + 2);
	if (!add)
		exit(error(0, "error allocation"));
	if (*s)
	{
		ft_strcpy(add, *s);
		free(*s);
	}
	add[len] = c;
	add[len + 1] = 0;
	*s = add;
}

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
	return (fd);
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
