/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:06:01 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/14 15:37:25 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*pwd(int x)
{
	char	buffer[PATH_MAX];

    if (getcwd(buffer, sizeof(buffer)))
        printf("%s\n", buffer);
    else
        perror("Error");
    return (0);
}