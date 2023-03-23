/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:06:01 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/22 11:33:19 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

char	*pwd(int is_child)
{
	char	buffer[PATH_MAX];

    if (getcwd(buffer, sizeof(buffer)))
        printf("%s\n", buffer);
    else
	{
        perror("Error");
		if (is_child)
			exit_status(127);
	}
    return (0);
}
