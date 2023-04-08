/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:06:01 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/08 15:39:16 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	pwd(int is_child)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)))
		printf("%s\n", buffer);
	else
	{
		perror("Error");
		if (is_child)
			exit_status(127, 1);
	}
}
