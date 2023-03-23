/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:04:06 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/17 08:34:46 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

int	check_n(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '-' && str[1] && str[1] == 'n')
		i++;
	else
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo(char **cmd)
{
	int i;
	int line;

	i = 1;
	line = 0;
	if (check_n(cmd[i]))
	{
		i++;
		line = 1;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
		if (cmd[i])
			printf(" ");
	}
	if (!line)
		printf("\n");
}